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

class WorldChunk;
class World;

class WorldChunkContainer
{
public:
	typedef std::unordered_map< glm::ivec2, std::shared_ptr< WorldChunk > > ChunkMap;
	typedef std::list< std::shared_ptr< WorldChunk > > ChunkList;

protected:
	World& m_world;
	ChunkMap m_chunkMap;
	ChunkList m_chunkList;

public:
	WorldChunkContainer( World& world );

	CUBIX_GET_R_CR( m_chunkList, AllChunks );

	std::shared_ptr< WorldChunk > getChunk( const glm::ivec2& chunkPos ) const;
	std::shared_ptr< WorldChunk > getOrCreateChunk( const glm::ivec2& chunkPos );
	void deleteChunk( const glm::ivec2& chunkPos );

	void setVoxel( const glm::ivec3& pos, const Voxel& voxel );
	Voxel getVoxel( const glm::ivec3& pos, const Voxel& _def = Voxel() ) const;
	void getVoxels( const Core::AxisAlignedBB& aabb, std::list< PlacedVoxel >& buffer );
};

} // namespace Game

#endif
