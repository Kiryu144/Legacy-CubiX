/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_CONTAINER_H
#define CUBIX_WORLD_CHUNK_CONTAINER_H

#include "core/cubix_macro.h"
#include "core/logic/lockable.h"

#include "game/world/voxel/placed_voxel.h"
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

namespace Core
{
class AxisAlignedBB;
}

namespace Game
{

class WorldChunkColumn;
class WorldChunk;
class World;

class WorldChunkContainer
{
public:
	typedef std::unordered_map< glm::ivec2, std::shared_ptr< WorldChunkColumn > > ChunkColumnMap;
	typedef std::unordered_set< std::shared_ptr< WorldChunk > > LoadedChunkList;

protected:
	World& m_world;
	ChunkColumnMap m_chunkColumnMap;
	std::mutex m_chunkColumnMapMutex;

	// This list does not neccessarily contain all chunks in existence
	// Chunks that were just created and are in the process of being
	// generated are not contained in this list
	LoadedChunkList m_allChunks;

	// Returns a chunkColumn in a given position. Returns nullptr if missing.
	std::shared_ptr< WorldChunkColumn > getChunkColumn( const glm::ivec2& chunkPos );

	// Returns a chunkColumn in a given position. If column is missing, a new one will be created
	// and returned.
	std::shared_ptr< WorldChunkColumn > getOrCreateChunkColumn( const glm::ivec2& chunkPos );

public:
	WorldChunkContainer( World& world );

	CUBIX_GET_R_CR( m_allChunks, AllChunks );

	// Returns a chunk in a given position. Returns nullptr if missing.
	std::shared_ptr< WorldChunk > getChunk( const glm::ivec3& chunkPos ) const;

	// Sets a voxel in a given worldposition. If the given voxel is not loaded, nothing will change.
	// Upon setting more than one voxel at a time, this method should not be used, as it is very
	// slow.
	void setVoxel( const glm::ivec3& pos, const Voxel& voxel );

	// Sets a voxel in a given worldposition. If the given voxel is not loaded, the default voxel
	// will be returned. Upon retrieving more than one voxel at a time, this method should not be
	// used, as it is very slow.
	Voxel getVoxel( const glm::ivec3& pos, const Voxel& _def = Voxel() ) const;

	// Returns a list of all voxels fully or partially contained in a given bounding box.
	void getVoxels( const Core::AxisAlignedBB& aabb, std::list< PlacedVoxel >& buffer );

	// Will be called by the worldgenerator once all chunks in the column have been generated.
	// This will result in all chunks from the given column to be added to the loaded list.
	void finalizeChunkColumn( const glm::ivec2& columnPos );

	// Returns if a given chunk exists in the world. This also includes non-loaded ones.
	bool doesChunkExist( const glm::ivec3& chunkPos ) const;

	// Returns a chunk at given position or creates a new one if that one is missing.
	// If so, it returns the new chunk.
	// Chunk will be created as a WorldChunk or RenderWorldChunk. This depends
	// on if a renderer is present in the owning world.
	std::shared_ptr< WorldChunk > getOrCreateChunk( const glm::ivec3& chunkPos );

	// Removed all references to a given chunk at position.
	// If chunkcolumn is empty after deletion, it will get deleted aswell.
	void deleteChunk( const glm::ivec3& chunkPos );

	void deleteColumn( const glm::ivec2& chunkPos );
};

} // namespace Game

#endif
