/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_container.h"

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
	return CUBIX_NCONST_GET(
		std::shared_ptr< WorldChunk >, WorldChunkContainer, getChunk( chunkPos ) );
}

bool WorldChunkContainer::getChunkExists( const glm::ivec3& chunkPos ) const
{
	return getChunk( chunkPos ).get() != nullptr;
}

std::shared_ptr< WorldChunk > WorldChunkContainer::createChunk( const glm::ivec3& chunkPos )
{
	auto column = getOrCreateChunkColumn( { chunkPos.x, chunkPos.z } );
	return column->createEmptyChunkIfAbsent( chunkPos.y );
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
	return CUBIX_NCONST_GET(
		std::shared_ptr< WorldChunkColumn >, WorldChunkContainer, getChunkColumn( chunkPos ) );
}

std::shared_ptr< WorldChunkColumn > WorldChunkContainer::getOrCreateChunkColumn(
	const glm::ivec2& chunkPos )
{
	if( const auto& ptr = getChunkColumn( chunkPos ) )
	{
		return ptr;
	}
	m_chunkColumnMap.insert( { chunkPos, { new WorldChunkColumn( m_world, chunkPos ) } } );
	return m_chunkColumnMap.find( chunkPos )->second;
}

} // namespace Game