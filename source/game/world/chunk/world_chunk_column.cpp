/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_column.h"

#include "game/world/chunk/render_world_chunk.h"
#include "game/world/world.h"

namespace Game
{

WorldChunkColumn::WorldChunkColumn( World& world, const glm::ivec2& chunkPosition )
	: m_world( world ), m_chunkPosition( chunkPosition )
{
}

std::shared_ptr< WorldChunk > WorldChunkColumn::getChunk( int yLevel ) const
{
	auto it = m_column.find( yLevel );
	return it != m_column.end() ? it->second : nullptr;
}

WorldChunkColumn::ColumnMap::mapped_type WorldChunkColumn::getOrCreateChunk( int yLevel )
{
	auto chunk{ getChunk( yLevel ) };
	if( chunk == nullptr )
	{
		glm::ivec3 chunkPosition{ m_chunkPosition.x, yLevel, m_chunkPosition.y };
		if( m_world.getRenderer() == nullptr )
		{
			// Server chunk
			chunk.reset( new WorldChunk( m_world, chunkPosition ) );
		}
		else
		{
			// Client chunk
			chunk.reset( new RenderWorldChunk( m_world, chunkPosition ) );
		}

		return m_column.insert( { yLevel, chunk } ).first->second;
	}
	else
	{
		return chunk;
	}
}

void WorldChunkColumn::deleteChunk( int yLevel )
{
	m_column.erase( yLevel );
}

size_t WorldChunkColumn::size() const
{
	return m_column.size();
}

} // namespace Game