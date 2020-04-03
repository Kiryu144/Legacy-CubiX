/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_H
#define CUBIX_WORLD_H

#include "core/cubix_macro.h"
#include "core/logic/lockable.h"
#include "core/logic/memory.h"
#include "core/math/glm_math.h"

#include "game/common/voxel/voxel_group.h"
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
	typedef std::unordered_set< glm::ivec3 > ChunkQueue;
	typedef std::list< std::weak_ptr< WorldChunk > > ChunkList;

protected:
	ChunkMap m_chunks;
	ChunkList m_weakChunkReference;
	ChunkWorker m_chunkWorker;
	Core::Lockable< ChunkQueue > m_chunksToGenerate;
	Core::Lockable< ChunkQueue > m_chunksToDelete;

	void _generateChunk( const glm::ivec3& chunkPosition );
	void _deleteChunk( const glm::ivec3& chunkPosition );

public:
	World();
	virtual ~World() = default;
	virtual void update( float deltaTime );

	CUBIX_GET_R_CR( m_weakChunkReference, AllChunks );
	CUBIX_GET_R_CR( m_chunkWorker, ChunkWorker );

	WorldChunkColumn::ColumnMap::mapped_type getChunk( const glm::ivec3& position );
	const WorldChunkColumn::ColumnMap::mapped_type getChunk( const glm::ivec3& position ) const;
	WorldChunkColumn::ColumnMap::mapped_type createEmptyChunkIfAbsent( const glm::ivec3& position );
	ChunkMap::mapped_type getChunkColumn( const glm::ivec2& position );


	void insert( const VoxelGroup& voxelGroup, glm::ivec3 position );

	void updateForPlayer( const glm::ivec2& chunkPosition );

	// Thread safe
	void generateChunk( const glm::ivec3& chunkPosition );
	void deleteChunk( const glm::ivec3& chunkPosition );
};

} // namespace Game

#endif
