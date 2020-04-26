/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk.h"

#include "game/world/world.h"

namespace Game
{

WorldChunk::WorldChunk( World& world, const glm::ivec3& chunkPosition )
	: m_world( world ), m_chunkPosition( chunkPosition )
{
}

void WorldChunk::setVoxel( const glm::uvec3& position, const Voxel& voxel )
{
	cubix_assert( !m_data.empty(), "Data hasn't been initialized yet" );
	auto& existingVoxel = m_data[ GetIndexForPosition( position ) ];
	if( existingVoxel.exists() != voxel.exists() )
	{
		m_voxelCount += voxel.exists() ? +1 : -1;
	}

	existingVoxel = voxel;
}

const Voxel& WorldChunk::getVoxel( const glm::uvec3& position ) const
{
	static const Voxel noVoxel;
	if( !isInitialized() )
	{
		return noVoxel;
	}
	return m_data[ GetIndexForPosition( position ) ];
}

size_t WorldChunk::getVoxelCount() const
{
	return m_voxelCount;
}

void WorldChunk::initializeData()
{
	cubix_assert( m_data.empty(), "Data was already initialized" );
	m_data.resize( GetVolume() );
}

bool WorldChunk::isInitialized() const
{
	return !m_data.empty();
}

} // namespace Game