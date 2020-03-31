/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_GENERATOR_H
#define CUBIX_WORLD_GENERATOR_H

#include "game/common/voxel/voxel.h"
#include "game/common/world/world.h"

#include <glm/vec2.hpp>

namespace Game
{

class WorldGenerator
{
protected:
	virtual void setVoxel( Voxel& voxel, unsigned int blocksUnderground );
	virtual int getHeight( const glm::ivec2& worldPosition );
	virtual void prepareForChunk( const glm::ivec3& chunkPosition ) {}

public:
	WorldGenerator() = default;

	void generateHeight( WorldChunk& chunk );
	int getSeed()
	{
		return 1234;
	}
};

} // namespace Game

#endif
