/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "placed_voxel.h"

namespace Game
{

PlacedVoxel::PlacedVoxel( World& world, const glm::ivec3& position, Voxel voxel )
	: Voxel( voxel ), m_world( world ), m_position( position )
{
}

} // namespace Game