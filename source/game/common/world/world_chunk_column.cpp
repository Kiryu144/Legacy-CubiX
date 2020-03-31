/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_column.h"

#include "game/common/world/world_chunk.h"

namespace Game
{

WorldChunkColumn::WorldChunkColumn( World& world, const glm::ivec2& chunkPosition )
	: m_world( world ),
	  m_chunkPosition( chunkPosition ),
	  m_yLevelLimits( { WorldChunk::s_sideLength, WorldChunk::s_sideLength } )
{
}

WorldChunkColumn::ColumnMap::mapped_type WorldChunkColumn::getChunk( int yLevel )
{
	auto it = m_column.find( yLevel );
	return it != m_column.end() ? it->second : nullptr;
}

const WorldChunkColumn::ColumnMap::mapped_type WorldChunkColumn::getChunk( int yLevel ) const
{
	auto cit = m_column.find( yLevel );
	return cit != m_column.end() ? cit->second : nullptr;
}

WorldChunkColumn::ColumnMap::mapped_type WorldChunkColumn::createEmptyChunkIfAbsent( int yLevel )
{
	ColumnMap::mapped_type chunk;
	if( getChunk( yLevel ).get() == nullptr )
	{
		chunk = m_column
					.insert( { yLevel,
							   std::shared_ptr< WorldChunk >( new WorldChunk(
								   m_world, { m_chunkPosition.x, yLevel, m_chunkPosition.y } ) ) } )
					.first->second;
	}
	return chunk;
}

} // namespace Game