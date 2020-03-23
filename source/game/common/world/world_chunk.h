/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_H
#define CUBIX_WORLD_CHUNK_H

#include "game/common/voxel/voxel_group.h"
#include "core/math/transform.h"

namespace Game
{

class WorldChunk : public VoxelGroup, public Core::Transform
{
public:
	static unsigned int s_sideLength;
	const glm::uvec3 m_chunkPosition;

public:
	WorldChunk( const glm::uvec3& chunkPosition );

	void generateFlat( unsigned int floorThickness );
	void generateBasicNoise();
};

} // namespace Game

#endif
