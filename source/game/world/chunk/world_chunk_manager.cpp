/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_manager.h"

#include "world_chunk_container.h"

#include "game/world/chunk/world_chunk.h"

namespace Game
{

WorldChunkManager::WorldChunkManager( WorldChunkContainer& chunkContainer )
	: m_chunkContainer( chunkContainer )
{
}

void WorldChunkManager::updateChunk( const glm::ivec3& chunkPosition )
{
	auto surroundingChunks = m_chunkContainer.getSurroundingChunks( chunkPosition );
	for( const auto& chunk : surroundingChunks )
	{
		
	}
}

} // namespace Game