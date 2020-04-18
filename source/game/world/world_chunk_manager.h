/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_MANAGER_H
#define CUBIX_WORLD_CHUNK_MANAGER_H

#include <glm/vec3.hpp>

namespace Game
{

class WorldChunkContainer;

class WorldChunkManager
{
protected:
	WorldChunkContainer& m_chunkContainer;

public:
	WorldChunkManager( WorldChunkContainer& chunkContainer );

	void updateChunk(const glm::ivec3& chunkPosition);
};

}

#endif
