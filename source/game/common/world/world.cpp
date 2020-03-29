/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world.h"

namespace Game
{

World::World() : m_chunkWorker( 1 ) {}

void World::loadChunk( const glm::ivec3& chunkPosition )
{
	std::shared_ptr< WorldChunk > chunk( new WorldChunk( chunkPosition ) );
	m_chunks.insert( { chunkPosition, chunk } );
	m_chunkWorker.queue( chunk, ChunkWorker::GENERATE_TERRAIN );
	m_chunkWorker.queue( chunk, ChunkWorker::GENERATE_FACES );
	m_chunkWorker.queue( chunk, ChunkWorker::GENERATE_MESH );
}

World::ChunkMap& World::getChunks()
{
	return m_chunks;
}

const World::ChunkMap& World::getChunks() const
{
	return m_chunks;
}

} // namespace Game