/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_CONTAINER_H
#define CUBIX_WORLD_CHUNK_CONTAINER_H

#include <list>
#include <memory>
#include <unordered_map>
#include <unordered_set>


#include "core/cubix_macro.h"

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
	typedef std::list< std::weak_ptr< WorldChunk > > ChunkList;

protected:
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
	std::shared_ptr< WorldChunk > getChunk( const glm::ivec3& chunkPos );
	std::shared_ptr< const WorldChunk > getChunk( const glm::ivec3& chunkPos ) const;

	std::vector< std::shared_ptr< WorldChunk > > getSurroundingChunks(const glm::ivec3& chunkPos);

	// Returns true if chunk exists, false if otherwise
	bool getChunkExists( const glm::ivec3& chunkPos ) const;

	// Creates an empty chunk instance
	std::shared_ptr< WorldChunk > createChunk( const glm::ivec3& chunkPos );

	void removeChunk( const glm::ivec3& chunkPos );

	CUBIX_GET_R_CR( m_allChunks, AllChunks );
};

} // namespace Game

#endif
