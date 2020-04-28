/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "entity.h"

#include "game/rendering/renderer.h"
#include "game/rendering/world/gizmo_renderer.h"
#include "game/world/voxel/placed_voxel.h"
#include "game/world/world.h"

namespace Game
{

Entity::Entity()
{
	getRotationOrigin() = getScale() * glm::vec3( 0.5f );
}

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

} // namespace Game
