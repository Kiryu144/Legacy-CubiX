/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_column.h"

#include "world.h"

#include "game/world/chunk/world_chunk.h"
#include "game/world/chunk/world_chunk_factory.h"

namespace Game
{

WorldChunkColumn::WorldChunkColumn( World& world, const glm::ivec2& chunkPosition )
	: m_world( world ), m_chunkPosition( chunkPosition )
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
	if( getChunk( yLevel ).get() == nullptr )
	{
		return m_column
			.insert( { yLevel,
					   std::shared_ptr< IWorldChunk >( m_world.getChunkFactory()->create(
						   m_world, { m_chunkPosition.x, yLevel, m_chunkPosition.y } ) ) } )
			.first->second;
	}
	return { nullptr };
}

void WorldChunkColumn::removeChunk( int yLevel )
{
	m_column.erase( yLevel );
}

size_t WorldChunkColumn::size() const
{
	return m_column.size();
}

} // namespace Game