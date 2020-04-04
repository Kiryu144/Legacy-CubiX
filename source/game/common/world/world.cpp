/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world.h"

#include "game/common/world/world_chunk.h"

namespace Game
{

World::World() : m_chunkWorker( 4 ) {}

void World::generateChunk( const glm::ivec3& chunkPosition )
{
	auto lock( m_chunksToGenerate.lockGuard() );
	m_chunksToGenerate.insert( chunkPosition );
}

void World::_generateChunk( const glm::ivec3& chunkPosition )
{
	auto chunk = createEmptyChunkIfAbsent( chunkPosition );
	if( chunk != nullptr )
	{
		m_chunkWorker.queue( chunk, ChunkWorker::GENERATE_TERRAIN );
		m_chunkWorker.queue( chunk, ChunkWorker::GENERATE_MESH );
	}
}

WorldChunkColumn::ColumnMap::mapped_type World::getChunk( const glm::ivec3& position )
{
	auto it = m_chunks.find( { position.x, position.z } );
	return it != m_chunks.end() ? it->second->getChunk( position.y ) : nullptr;
}

const WorldChunkColumn::ColumnMap::mapped_type World::getChunk( const glm::ivec3& position ) const
{
	auto cit = m_chunks.find( { position.x, position.z } );
	return cit != m_chunks.end() ? cit->second->getChunk( position.y ) : nullptr;
}

WorldChunkColumn::ColumnMap::mapped_type World::createEmptyChunkIfAbsent(
	const glm::ivec3& position )
{
	auto it = m_chunks.find( { position.x, position.z } );
	if( it == m_chunks.end() )
	{
		it = m_chunks
				 .insert( { { position.x, position.z },
							ChunkMap::mapped_type(
								new WorldChunkColumn( *this, { position.x, position.z } ) ) } )
				 .first;
	}
	auto chunk = it->second->createEmptyChunkIfAbsent( position.y );

	if( chunk != nullptr )
	{
		m_weakChunkReference.push_back( ChunkList::value_type( chunk ) );
	}
	return chunk;
}

void World::update( float deltaTime )
{
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

	for( auto it = m_weakChunkReference.begin(); it != m_weakChunkReference.end(); )
	{
		if( it->expired() )
		{
			it = m_weakChunkReference.erase( it );
		}
		else
		{
			auto chunk = it->lock();
			chunk->setMillisecondsNotSeen( chunk->getMillisecondsNotSeen() + deltaTime );

			if( chunk->getMillisecondsNotSeen() > 2500 )
			{
				deleteChunk( chunk->getChunkPosition() );
			}

			++it;
		}
	}
}

void World::insert( const VoxelGroup& voxelGroup, glm::ivec3 position )
{
	glm::ivec3 lowestChunkPos{ WorldChunk::WorldPosToChunkPos( position ) };
	glm::ivec3 affectedChunks{ static_cast< glm::ivec3 >( voxelGroup.getSize() )
								   / glm::ivec3( WorldChunk::s_sideLength )
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
					chunk = createEmptyChunkIfAbsent( chunkPosition );
				}

				chunk->WorldChunk::lock();

				glm::ivec3 v = position
					- ( ( chunkPosition  )
						* glm::ivec3( WorldChunk::s_sideLength ) );
				chunk->insert( voxelGroup, v );

				chunk->WorldChunk::unlock();
				m_chunkWorker.queue( chunk, ChunkWorker::GENERATE_MESH );
			}
		}
	}
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

std::shared_ptr< WorldChunkColumn > World::getChunkColumn( const glm::ivec2& position )
{
	auto it = m_chunks.find( position );
	return it != m_chunks.end() ? it->second : nullptr;
}

void World::_deleteChunk( const glm::ivec3& chunkPosition )
{
	auto chunkColumn = getChunkColumn( { chunkPosition.x, chunkPosition.z } );
	if( chunkColumn )
	{
		chunkColumn->deleteChunk( chunkPosition.y );
		if( chunkColumn->size() == 0 )
		{
			m_chunks.erase( { chunkPosition.x, chunkPosition.z } );
		}
	}
}

void World::deleteChunk( const glm::ivec3& chunkPosition )
{
	auto lock( m_chunksToDelete.lockGuard() );
	m_chunksToDelete.insert( chunkPosition );
}

} // namespace Game