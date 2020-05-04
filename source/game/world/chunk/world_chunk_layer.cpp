/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_layer.h"

namespace Game
{

WorldChunkLayer::WorldChunkLayer( WorldChunk& worldChunk, int yLevel )
	: m_worldChunk( worldChunk ), m_yLevel( yLevel )
{
}

void WorldChunkLayer::setVoxel( const glm::ivec2& position, Voxel voxel )
{
	auto& existingVoxel = m_data[ GetIndexForLayer( position ) ];
	if( existingVoxel.exists() != voxel.exists() )
	{
		m_voxelCount += voxel.exists() ? +1 : -1;
	}
	existingVoxel = voxel;
}

Voxel WorldChunkLayer::getVoxel( const glm::ivec2& position ) const
{
	return m_data[ GetIndexForLayer( position ) ];
}

void WorldChunkLayer::setVoxel( size_t index, Voxel voxel )
{
	auto& existingVoxel = m_data[ index ];
	if( existingVoxel.exists() != voxel.exists() )
	{
		m_voxelCount += voxel.exists() ? +1 : -1;
	}
	existingVoxel = voxel;
}

Voxel WorldChunkLayer::getVoxel( size_t index ) const
{
	return m_data[ index ];
}

} // namespace Game
