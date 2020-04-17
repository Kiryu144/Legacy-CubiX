/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world.h"

#include "game/common/world/chunk/world_chunk.h"

namespace Game
{

World::World()
	: WorldChunkContainer( *this ),
	  m_chunkWorker( 4 ),
	  m_chunkFactory( new RenderWorldChunkFactory() )
{
}

void World::generateChunk( const glm::ivec3& chunkPosition )
{
	auto lock( m_chunksToGenerate.lockGuard() );
	m_chunksToGenerate.insert( chunkPosition );
}

void World::_generateChunk( const glm::ivec3& chunkPosition )
{
	auto chunk = createChunk( chunkPosition );
	if( chunk != nullptr )
	{
		m_chunkWorker.queue( chunk );
	}
}

void World::update( float deltaTime )
{
	m_chunkWorker.checkForCrash();
	{
		auto lock( m_chunksToGenerate.lockGuard() );
		for( auto& chunkPosition : m_chunksToGenerate )
		{
			_generateChunk( chunkPosition );
		}
		m_chunksToGenerate.clear();
	}

	{
		auto lock( m_chunksToDelete.lockGuard() );
		for( auto& chunkPosition : m_chunksToDelete )
		{
			_deleteChunk( chunkPosition );
		}
		m_chunksToDelete.clear();
	}

	for( auto it = m_allChunks.begin(); it != m_allChunks.end(); )
	{
		if( it->expired() )
		{
			it = m_allChunks.erase( it );
		}
		else
		{
			auto chunk = it->lock();
			chunk->setMillisecondsNotSeen( chunk->getMillisecondsNotSeen() + deltaTime * 1000 );
			if( chunk->getMillisecondsNotSeen() > 500 )
			{
				deleteChunk( chunk->getChunkPosition() );
			}

			++it;
		}
	}
}

void World::insert( const VoxelGroup& voxelGroup, glm::ivec3 position )
{
	/*
	glm::ivec3 lowestChunkPos{ IWorldChunk::ChunkPosFromWorldPos( position ) };
	glm::ivec3 affectedChunks{ static_cast< glm::ivec3 >( voxelGroup.getSize() )
								   / glm::ivec3( IWorldChunk::GetSideLength() )
							   + glm::ivec3( 2 ) };

	for( int x = 0; x < affectedChunks.x; ++x )
	{
		for( int y = 0; y < affectedChunks.y; ++y )
		{
			for( int z = 0; z < affectedChunks.z; ++z )
			{
				glm::ivec3 chunkPosition{ lowestChunkPos + glm::ivec3{ x, y, z } };
				auto chunk = getChunk( chunkPosition );
				if( !chunk )
				{
					chunk = createChunk( chunkPosition );
				}

				chunk->WorldChunk::lock();

				glm::ivec3 v
					= position - ( ( chunkPosition )*glm::ivec3( IWorldChunk::GetSideLength() ) );
				chunk->insert( voxelGroup, v );

				chunk->WorldChunk::unlock();
				// m_chunkWorker.queue( chunk );
			}
		}
	}*/
}

void World::updateForPlayer( const glm::ivec2& chunkPosition )
{
	auto chunkColumn = getChunkColumn( chunkPosition );
	if( chunkColumn == nullptr )
	{
		generateChunk( { chunkPosition.x, 0, chunkPosition.y } );
	}
	else
	{
		for( auto it : chunkColumn->getChunks() )
		{
			it.second->setMillisecondsNotSeen( 0 );
		}
	}
}

void World::_deleteChunk( const glm::ivec3& chunkPosition )
{
	removeChunk( chunkPosition );
}

void World::deleteChunk( const glm::ivec3& chunkPosition )
{
	auto lock( m_chunksToDelete.lockGuard() );
	m_chunksToDelete.insert( chunkPosition );
}

} // namespace Game