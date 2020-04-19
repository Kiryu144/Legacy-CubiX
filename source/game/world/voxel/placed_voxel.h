/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PLACED_VOXEL_H
#define CUBIX_PLACED_VOXEL_H

#include "core/cubix_macro.h"

#include "game/world/voxel/voxel.h"

namespace Game
{

class World;

class PlacedVoxel : public Voxel
{
protected:
	World& m_world;
	glm::ivec3 m_position;

public:
	PlacedVoxel( World& world, const glm::ivec3& position, Voxel voxel = Voxel() );

	CUBIX_GET_CR( m_world, World );
	CUBIX_GET_CR( m_position, Position );
};

} // namespace Game

#endif
