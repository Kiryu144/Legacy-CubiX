/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_H
#define CUBIX_WORLD_H

#include "core/cubix_macro.h"
#include "core/data/lockable.h"
#include "core/data/memory.h"
#include "core/math/glm_math.h"

#include "game/common/world/chunk_worker.h"
#include "game/common/world/world_chunk_column.h"
#include "game/proxy.h"

#include <set>
#include <unordered_map>
#include <unordered_set>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace Game
{

class World
{
public:
	typedef std::unordered_map< glm::ivec2, std::shared_ptr< WorldChunkColumn > > ChunkMap;
	typedef std::unordered_set< glm::ivec3 > ChunkGenerationQueue;
	typedef std::list< std::weak_ptr< WorldChunk > > ChunkList;

protected:
	ChunkMap m_chunks;
	ChunkList m_weakChunkReference;
	ChunkWorker m_chunkWorker;
	Core::Lockable< ChunkGenerationQueue > m_chunksToGenerate;

	void _generateChunk( const glm::ivec3& chunkPosition );

public:
	World();
	virtual ~World() = default;
	virtual void update( float deltaTime );

	CUBIX_GET_R_CR( m_weakChunkReference, AllChunk );

	WorldChunkColumn::ColumnMap::mapped_type getChunk( const glm::ivec3& position );
	const WorldChunkColumn::ColumnMap::mapped_type getChunk( const glm::ivec3& position ) const;
	WorldChunkColumn::ColumnMap::mapped_type createEmptyChunkIfAbsent( const glm::ivec3& position );

	// Thread safe
	void generateChunk( const glm::ivec3& chunkPosition );
};

} // namespace Game

#endif
