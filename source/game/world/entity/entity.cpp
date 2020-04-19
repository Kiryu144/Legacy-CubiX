/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "entity.h"

#include "game/rendering/gizmo_renderer.h"
#include "game/rendering/renderer.h"
#include "game/world/voxel/placed_voxel.h"
#include "game/world/world.h"

namespace Game
{

void Entity::update( World& world, float deltaTime )
{
	Core::AxisAlignedBB myBB = m_axisAlignedBb;
	myBB.offset( m_position );

	std::list< PlacedVoxel > voxels;
	world.getVoxels( myBB, voxels );

	for( auto& voxel : voxels )
	{
		if( !voxel.exists() )
		{
			continue;
		}
		Core::AxisAlignedBB voxelBB{ Core::AxisAlignedBB::FromPosition( voxel.getPosition() ) };
		if( myBB.intersectsWith( voxelBB ) )
		{
			glm::vec3 offset = myBB.calculateOffset( voxelBB, getVelocity() );
			getVelocity() -= offset;
		}
	}

	Core::Rigidbody::update( deltaTime );
}

/*
void Entity::update( World& world, float deltaTime )
{
	std::list< PlacedVoxel > voxels;
	glm::vec3 offset;
	for( int i = 0; i < 3; ++i )
	{
		Core::AxisAlignedBB myBB = m_axisAlignedBb;
		myBB.offset( m_position );
		voxels.clear();
		world.getVoxels( myBB, voxels );

		for( auto& voxel : voxels )
		{
			if( !voxel.exists() )
			{
				continue;
			}
			Core::AxisAlignedBB voxelBB{ Core::AxisAlignedBB::FromPosition( voxel.getPosition() ) };

			switch( i )
			{
			case 1:
				offset[ i ] = myBB.calculateYOffset( voxelBB, getVelocity()[ i ] );
				break;
			case 0:
				offset[ i ] = myBB.calculateXOffset( voxelBB, getVelocity()[ i ] );
				break;
			case 2:
				offset[ i ] = myBB.calculateZOffset( voxelBB, getVelocity()[ i ] );
				break;
			}
		}
	}

	getVelocity() -= offset;
	Core::Rigidbody::update( deltaTime );
}

*/

} // namespace Game
