/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "voxel_clipboard.h"

#include <math.h>

namespace Game
{

void VoxelClipboard::createSphere( unsigned int radius, const Voxel& voxel )
{
	m_voxelGroup.reset( new VoxelGroup( glm::uvec3( radius * 2 ) ) );

	glm::uvec3 center = glm::uvec3( radius );
	for( unsigned int x = 0; x < m_voxelGroup->getSize().x; ++x )
	{
		for( unsigned int y = 0; y < m_voxelGroup->getSize().y; ++y )
		{
			for( unsigned int z = 0; z < m_voxelGroup->getSize().z; ++z )
			{
				glm::uvec3 pos{ x, y, z };
				double distance{ std::sqrt(
					std::pow( static_cast< float >( pos.x ) - center.x, 2 )
					+ std::pow( static_cast< float >( pos.y ) - center.y, 2 )
					+ std::pow( static_cast< float >( pos.z ) - center.z, 2 ) ) };

				if( distance < radius )
				{
					m_voxelGroup->set( pos, voxel );
				}
			}
		}
	}
}

void VoxelClipboard::createCube( unsigned int sideLength, const Voxel& voxel )
{
	m_voxelGroup.reset( new VoxelGroup( glm::uvec3( sideLength ) ) );

	for( unsigned int x = 0; x < m_voxelGroup->getSize().x; ++x )
	{
		for( unsigned int y = 0; y < m_voxelGroup->getSize().y; ++y )
		{
			for( unsigned int z = 0; z < m_voxelGroup->getSize().z; ++z )
			{
				m_voxelGroup->set( { x, y, z }, voxel );
			}
		}
	}
}

} // namespace Game