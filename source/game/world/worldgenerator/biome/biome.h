/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_BIOME_H
#define CUBIX_BIOME_H

#include "core/cubix_macro.h"

namespace Game
{

class Voxel;

class Biome
{
protected:
	int m_baseHeight{ 0 };
	int m_heightVariation{ 0 };

public:
	Biome( int baseHeight, int heightVariation );

	CUBIX_GET_CR( m_baseHeight, BaseHeight );
	CUBIX_GET_CR( m_heightVariation, HeightVariation );

	virtual Voxel getVoxelForDepth(unsigned int depth) const;
};

} // namespace Game

#endif
