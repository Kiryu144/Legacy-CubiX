/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_container.h"

#include "core/math/axis_aligned_bb.h"

#include "game/world/chunk/world_chunk.h"
#include "game/world/chunk/world_chunk_column.h"
#include "game/world/world.h"

#include <shared_mutex>

namespace Game
{

WorldChunkContainer::WorldChunkContainer( World& world ) : m_world( world ) {}

std::shared_ptr< WorldChunk > WorldChunkContainer::getChunk( const glm::ivec3& chunkPos ) const
{
	auto it = m_chunkColumnMap.find( { chunkPos.x, chunkPos.z } );
	if( it == m_chunkColumnMap.end() )
	{
		return nullptr;
	}
	return it->second->getChunk( chunkPos.y );
}

bool WorldChunkContainer::doesChunkExist( const glm::ivec3& chunkPos ) const
{
	return m_chunkColumnMap.find( { chunkPos.x, chunkPos.z } ) != m_chunkColumnMap.end();
}

std::shared_ptr< WorldChunk > WorldChunkContainer::getOrCreateChunk( const glm::ivec3& chunkPos )
{
	auto column = getOrCreateChunkColumn( { chunkPos.x, chunkPos.z } );
	return column->getOrCreateChunk( chunkPos.y );
}

std::shared_ptr< WorldChunkColumn > WorldChunkContainer::getChunkColumn(
	const glm::ivec2& chunkPos )
{
	auto it = m_chunkColumnMap.find( chunkPos );
	return it != m_chunkColumnMap.end() ? it->second : nullptr;
}

std::shared_ptr< WorldChunkColumn > WorldChunkContainer::getOrCreateChunkColumn(
	const glm::ivec2& chunkPos )
{
	auto it = m_chunkColumnMap.find( chunkPos );
	if( it != m_chunkColumnMap.end() )
	{
		return it->second;
	}

	return m_chunkColumnMap
		.insert(
			{ chunkPos,
			  std::shared_ptr< WorldChunkColumn >( new WorldChunkColumn( m_world, chunkPos ) ) } )
		.first->second;
}

void WorldChunkContainer::deleteChunk( const glm::ivec3& chunkPos )
{
	auto column = getChunkColumn( glm::ivec2{ chunkPos.x, chunkPos.z } );
	if( column != nullptr )
	{
		column->deleteChunk( chunkPos.y );
		if( column->size() == 0 )
		{
			m_chunkColumnMap.erase( { chunkPos.x, chunkPos.z } );
		}
	}
}

Voxel WorldChunkContainer::getVoxel( const glm::ivec3& pos, const Voxel& _def ) const
{
	auto chunk = getChunk( WorldChunk::ChunkPosFromWorldPos( pos ) );
	if( chunk == nullptr )
	{
		return _def;
	}
	return chunk->getVoxel( pos - WorldChunk::WorldPosFromChunkPos( chunk->getChunkPosition() ) );
}

void WorldChunkContainer::setVoxel( const glm::ivec3& pos, const Voxel& voxel )
{
	auto chunk = getChunk( WorldChunk::ChunkPosFromWorldPos( pos ) );
	if( chunk == nullptr )
	{
		return;
	}
	return chunk->setVoxel( pos - WorldChunk::WorldPosFromChunkPos( chunk->getChunkPosition() ),
							voxel );
}

void WorldChunkContainer::getVoxels( const Core::AxisAlignedBB& aabb,
									 std::list< PlacedVoxel >& buffer )
{
	glm::ivec3 min{ std::floor( aabb.getMin().x ),
					std::floor( aabb.getMin().y ),
					std::floor( aabb.getMin().z ) };
	glm::ivec3 max{ std::floor( aabb.getMax().x ),
					std::floor( aabb.getMax().y ),
					std::floor( aabb.getMax().z ) };

	// Optimize by caching chunks ( getVoxel() is slow )
	for( int x = min.x; x <= max.x; ++x )
	{
		for( int y = min.y; y <= max.y; ++y )
		{
			for( int z = min.z; z <= max.z; ++z )
			{
				glm::ivec3 pos{ x, y, z };
				buffer.push_back( PlacedVoxel( m_world, pos, getVoxel( pos ) ) );
			}
		}
	}
}

void WorldChunkContainer::finalizeChunkColumn( const glm::ivec2& columnPos )
{
	auto column = getChunkColumn( columnPos );
	if( column != nullptr )
	{
		for( auto& chunk : column->getChunkColumnData() )
		{
			m_allChunks.insert( chunk.second );
		}
	}
}

} // namespace Game