/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_container.h"

#include "core/math/axis_aligned_bb.h"

#include "game/world/chunk/world_chunk.h"
#include "game/world/world.h"

#include <shared_mutex>

namespace Game
{

WorldChunkContainer::WorldChunkContainer( World& world ) : m_world( world ) {}

std::shared_ptr< WorldChunk > WorldChunkContainer::getChunk( const glm::ivec2& chunkPos ) const
{
	auto it = m_chunkMap.find( chunkPos );
	return it != m_chunkMap.end() ? it->second : nullptr;
}

void WorldChunkContainer::setVoxel( const glm::ivec3& pos, const Voxel& voxel )
{
	auto chunk = getChunk( pos );
	if( chunk )
	{
		chunk->setVoxel( WorldChunk::InsideChunkOffsetFromWorldPos( pos ), voxel );
	}
}

Voxel WorldChunkContainer::getVoxel( const glm::ivec3& pos, const Voxel& _def ) const
{
	auto chunk = getChunk( pos );
	if( !chunk )
	{
		return Voxel();
	}
	return chunk->getVoxel( WorldChunk::InsideChunkOffsetFromWorldPos( pos ) );
}

std::shared_ptr< WorldChunk > WorldChunkContainer::getOrCreateChunk( const glm::ivec2& chunkPos )
{
	auto chunk = getChunk( chunkPos );
	if( !chunk )
	{
		chunk.reset( new WorldChunk( m_world, chunkPos ) );
		m_chunkMap.insert( { chunkPos, chunk } );
		m_chunkList.push_back( chunk );
	}
	return chunk;
}

void WorldChunkContainer::deleteChunk( const glm::ivec2& chunkPos )
{
	m_chunkMap.erase( chunkPos );
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

} // namespace Game