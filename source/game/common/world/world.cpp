/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world.h"

#include "game/common/world/world_chunk.h"

namespace Game
{

World::World() : m_chunkWorker( 1 ) {}

void World::generateChunk( const glm::ivec3& chunkPosition )
{
	auto chunk = createEmptyChunkIfAbsent( chunkPosition );
	if( chunk != nullptr )
	{
		m_chunkWorker.queue( chunk, ChunkWorker::GENERATE_TERRAIN );
		m_chunkWorker.queue( chunk, ChunkWorker::GENERATE_FACES );
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
	for( auto it = m_weakChunkReference.begin(); it != m_weakChunkReference.end(); )
	{
		if( it->expired() )
		{
			it = m_weakChunkReference.erase( it );
		}
		else
		{
			++it;
		}
	}
}

} // namespace Game