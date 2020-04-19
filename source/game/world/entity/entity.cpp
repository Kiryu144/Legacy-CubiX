/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "entity.h"

#include "game/world/world.h"

namespace Game
{

void Entity::update( World& world, float deltaTime )
{
	Core::AxisAlignedBB myBB = m_axisAlignedBb;
	myBB.offset( m_position );

	for( int x = -1; x < 1; ++x )
	{
		for( int y = -1; y < 1; ++y )
		{
			for( int z = -1; z < 1; ++z )
			{
				glm::ivec3 worldVoxelPos{ static_cast< int >( m_position.x + x ),
										  static_cast< int >( m_position.y + y ),
										  static_cast< int >( m_position.z + z ) };

				auto voxel = world.getVoxel( m_position + glm::vec3{ x, y, z } );
				if( !voxel.exists() )
				{
					continue;
				}

				Core::AxisAlignedBB voxelBB{ Core::AxisAlignedBB::FromPosition( worldVoxelPos ) };
				if( myBB.intersectsWith( voxelBB ) )
				{
					glm::vec3 offset = myBB.calculateOffset( voxelBB, getVelocity() );
					getVelocity() -= offset;
				}
			}
		}
	}

	Core::Rigidbody::update( deltaTime );
}

} // namespace Game
