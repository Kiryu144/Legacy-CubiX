/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_container.h"

#include "core/cubix_macro.h"
#include "core/data/multiple_facing.h"

#include "game/common/world/world_chunk_column.h"

namespace Game
{

WorldChunkContainer::WorldChunkContainer( World& world ) : m_world( world ) {}

std::shared_ptr< const WorldChunk > WorldChunkContainer::getChunk(
	const glm::ivec3& chunkPos ) const
{
	auto it = m_chunkColumnMap.find( { chunkPos.x, chunkPos.z } );
	if( it == m_chunkColumnMap.end() )
	{
		return nullptr;
	}
	return it->second->getChunk( chunkPos.y );
}

std::shared_ptr< WorldChunk > WorldChunkContainer::getChunk( const glm::ivec3& chunkPos )
{
	auto it = m_chunkColumnMap.find( { chunkPos.x, chunkPos.z } );
	if( it == m_chunkColumnMap.end() )
	{
		return nullptr;
	}
	return it->second->getChunk( chunkPos.y );
}

bool WorldChunkContainer::getChunkExists( const glm::ivec3& chunkPos ) const
{
	return getChunk( chunkPos ).get() != nullptr;
}

std::shared_ptr< WorldChunk > WorldChunkContainer::createChunk( const glm::ivec3& chunkPos )
{
	auto column = getOrCreateChunkColumn( { chunkPos.x, chunkPos.z } );
	auto chunk	= column->createEmptyChunkIfAbsent( chunkPos.y );
	if( chunk != nullptr )
	{
		m_allChunks.push_back( chunk );
	}
	return chunk;
}

std::shared_ptr< WorldChunkColumn > WorldChunkContainer::getChunkColumn(
	const glm::ivec2& chunkPos )
{
	auto it = m_chunkColumnMap.find( chunkPos );
	return it != m_chunkColumnMap.end() ? it->second : nullptr;
}

std::shared_ptr< const WorldChunkColumn > WorldChunkContainer::getChunkColumn(
	const glm::ivec2& chunkPos ) const
{
	auto it = m_chunkColumnMap.find( chunkPos );
	return it != m_chunkColumnMap.end() ? it->second : nullptr;
}

std::shared_ptr< WorldChunkColumn > WorldChunkContainer::getOrCreateChunkColumn(
	const glm::ivec2& chunkPos )
{
	if( const auto& ptr = getChunkColumn( chunkPos ) )
	{
		return ptr;
	}
	m_chunkColumnMap.insert(
		{ chunkPos,
		  std::shared_ptr< WorldChunkColumn >( new WorldChunkColumn( m_world, chunkPos ) ) } );
	return m_chunkColumnMap.find( chunkPos )->second;
}

void WorldChunkContainer::removeChunk( const glm::ivec3& chunkPos )
{
	auto column = getChunkColumn( chunkPos );
	if( column != nullptr )
	{
		column->removeChunk( chunkPos.y );
		if( column->size() == 0 )
		{
			m_chunkColumnMap.erase( { chunkPos.x, chunkPos.z } );
		}
	}
}

std::vector< std::shared_ptr< WorldChunk > > WorldChunkContainer::getSurroundingChunks(
	const glm::ivec3& chunkPos )
{
	std::vector< std::shared_ptr< WorldChunk > > vec;
	vec.reserve( Core::MultipleFacing::Facings.size() );
	for( const auto& face : Core::MultipleFacing::Facings )
	{
		vec.push_back(
			getChunk( chunkPos + glm::ivec3( Core::MultipleFacing::DirectionOf( face ) ) ) );
	}
	return vec;
}

} // namespace Game