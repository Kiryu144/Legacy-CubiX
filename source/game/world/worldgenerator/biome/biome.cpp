/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "biome.h"

#include "game/world/voxel/voxel.h"

namespace Game
{

Biome::Biome( int baseHeight, int heightVariation )
	: m_baseHeight( baseHeight ), m_heightVariation( heightVariation )
{
}

Voxel Biome::getVoxelForDepth( unsigned int depth ) const
{
	switch( depth )
	{
	case 0:
	case 1:
		return { 65, 152, 10, 255 };
	case 2:
	case 3:
		return { 124, 83, 77, 255 };
	default:
		return { 141, 141, 141, 255 };
	}
}

} // namespace Game