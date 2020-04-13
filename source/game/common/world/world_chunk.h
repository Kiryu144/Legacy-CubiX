/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_H
#define CUBIX_WORLD_CHUNK_H

#include "core/data/container2d.h"
#include "core/logic/memory.h"
#include "core/logic/serializeable.h"
#include "core/math/transform.h"
#include "core/opengl/attributebuffer.h"
#include "core/opengl/data/interleaved_attribute.h"

#include "game/client/rendering/renderable.h"
#include "game/common/voxel/voxel_group.h"
#include "game/common/world/world.h"

#include <set>

namespace Game
{

class World;
class Entity;

class WorldChunk : public virtual VoxelGroup,
				   public Core::Transform,
				   public std::mutex
{
public:
	enum class State : int
	{
		NEW					 = 0,
		TERRAIN_GENERATED	 = 1,
		TERRAIN_POPULATED	 = 2,
		TERRAIN_MESH_CREATED = 3,
		DONE				 = 4
	};

	static unsigned int s_sideLength;
	static glm::ivec3 WorldPosToChunkPos( const glm::vec3& worldPos )
	{
		return glm::ivec3{ std::floor( worldPos.x / s_sideLength ),
						   std::floor( worldPos.y / s_sideLength ),
						   std::floor( worldPos.z / s_sideLength ) };
	}

protected:
	State m_chunkState{ State::NEW };
	glm::ivec3 m_chunkPosition;
	double m_millisecondsNotSeen{ 0 };
	World& m_world;

	Core::Container2D<int> m_highestBlock;

public:
	WorldChunk( World& world, const glm::ivec3& chunkPosition = glm::ivec3{ 0, 0, 0 } );

	CUBIX_GET_SET_R_CR( m_chunkPosition, ChunkPosition );
	CUBIX_GET_SET_R_CR( m_millisecondsNotSeen, MillisecondsNotSeen );
	CUBIX_GET_SET_CR_CR( m_chunkState, ChunkState );

	const glm::ivec3 getWorldPosition() const;

	unsigned int getSideLength();

	World& getWorld() const;

	int updateHighestBlock(const glm::ivec2& pos);
	void updateHighestBlocks();

	void serialize( std::ostream& out ) const override;
	void deserialize( std::istream& in ) override;
};

} // namespace Game

#endif
