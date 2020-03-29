/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_H
#define CUBIX_WORLD_H

#include "world_chunk.h"

#include "core/data/memory.h"
#include "core/math/glm_math.h"

#include "game/common/world/chunk_worker.h"
#include "game/proxy.h"

#include <set>
#include <unordered_map>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace Game
{

class World
{
public:
	typedef std::unordered_map< glm::ivec3, std::shared_ptr< WorldChunk > > ChunkMap;

protected:
	// All chunks loaded in the world
	ChunkMap m_chunks;
	ChunkWorker m_chunkWorker;

public:
	World();
	virtual ~World() = default;
	virtual void update( float deltaTime ){};

	void loadChunk( const glm::ivec3& chunkPosition );

	ChunkMap& getChunks();
	const ChunkMap& getChunks() const;
};

} // namespace Game

#endif
