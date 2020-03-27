/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_H
#define CUBIX_WORLD_CHUNK_H

#include "core/math/transform.h"

#include "game/common/voxel/voxel_group.h"

#include <mutex>

namespace Game
{

class WorldChunk : public VoxelGroup, public Core::Transform
{
public:
	std::mutex m_mutex;

	static unsigned int s_sideLength;
	const glm::ivec3 m_chunkPosition;

public:
	WorldChunk( const glm::ivec3& chunkPosition );

	void generateFlat( unsigned int floorThickness );
	void generateBasicNoise();

	std::mutex& getMutex();
	const std::mutex& getMutex() const;
};

} // namespace Game

#endif
