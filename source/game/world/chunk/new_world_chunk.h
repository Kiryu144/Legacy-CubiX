/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_NEW_WORLD_CHUNK_H
#define CUBIX_NEW_WORLD_CHUNK_H

#include "game/world/chunk/empty_world_chunk.h"

namespace Game
{

class NewWorldChunk : public EmptyWorldChunk
{
public:
	NewWorldChunk( World& world, const glm::ivec3& chunkPosition )
		: EmptyWorldChunk( world, chunkPosition )
	{
	}

};

} // namespace Game

#endif
