/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_FACTORY_H
#define CUBIX_WORLD_CHUNK_FACTORY_H

#include "empty_world_chunk.h"
#include "render_world_chunk.h"

namespace Game
{

class World;

struct IWorldChunkFactory
{
	virtual IWorldChunk* create( World& world, const glm::ivec3& chunkPosition ) const = 0;
};

struct WorldChunkFactory : public IWorldChunkFactory
{
	IWorldChunk* create( World& world, const glm::ivec3& chunkPosition ) const override
	{
		return new WorldChunk( world, chunkPosition );
	}
};

struct RenderWorldChunkFactory : public IWorldChunkFactory
{
	IWorldChunk* create( World& world, const glm::ivec3& chunkPosition ) const override
	{
		return new RenderWorldChunk( world, chunkPosition );
	}
};

struct EmptyWorldChunkFactory : public IWorldChunkFactory
{
	IWorldChunk* create( World& world, const glm::ivec3& chunkPosition ) const override
	{
		return new EmptyWorldChunk( world, chunkPosition );
	}
};

} // namespace Game

#endif // CUBIX_WORLD_CHUNK_FACTORY_H
