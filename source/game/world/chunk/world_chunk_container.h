/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_CONTAINER_H
#define CUBIX_WORLD_CHUNK_CONTAINER_H

#include "core/cubix_macro.h"
#include "core/logic/lockable.h"

#include "game/world/chunk/i_world_chunk.h"
#include "game/world/voxel/voxel.h"

#include <list>
#include <memory>
#include <unordered_map>
#include <unordered_set>

// clang-format off
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
// clang-format on

namespace Game
{

class WorldChunkColumn;
class WorldChunk;
class World;

class WorldChunkContainer
{
public:
	typedef std::unordered_map< glm::ivec2, std::shared_ptr< WorldChunkColumn > > ChunkColumnMap;
	typedef std::list< std::weak_ptr< IWorldChunk > > ChunkList;

protected:
	std::mutex m_chunkColumnMutex;
	ChunkColumnMap m_chunkColumnMap;
	ChunkList m_allChunks;
	World& m_world;

	// Get chunk column for a given 2D chunkposition. Returns nullptr if missing.
	std::shared_ptr< WorldChunkColumn > getChunkColumn( const glm::ivec2& chunkPos );
	std::shared_ptr< const WorldChunkColumn > getChunkColumn( const glm::ivec2& chunkPos ) const;

	std::shared_ptr< WorldChunkColumn > getOrCreateChunkColumn( const glm::ivec2& chunkPos );

public:
	WorldChunkContainer( World& world );

	// Get chunk from a given chunkpos. Returns nullptr if missing
	std::shared_ptr< IWorldChunk > getChunk( const glm::ivec3& chunkPos );
	std::shared_ptr< const IWorldChunk > getChunk( const glm::ivec3& chunkPos ) const;

	Voxel getVoxel( const glm::ivec3& pos, const Voxel& _def = Voxel() ) const;

	std::vector< std::shared_ptr< IWorldChunk > > getSurroundingChunks( const glm::ivec3& chunkPos );

	// Returns true if chunk exists, false if otherwise
	bool getChunkExists( const glm::ivec3& chunkPos ) const;

	// Creates an empty chunk instance
	std::shared_ptr< IWorldChunk > createChunk( const glm::ivec3& chunkPos );

	void removeChunk( const glm::ivec3& chunkPos );

	CUBIX_GET_R_CR( m_allChunks, AllChunks );
};

} // namespace Game

#endif