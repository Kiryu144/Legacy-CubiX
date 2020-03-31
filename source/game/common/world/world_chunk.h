/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_H
#define CUBIX_WORLD_CHUNK_H

#include "core/data/container2d.h"
#include "core/data/memory.h"
#include "core/data/serializeable.h"
#include "core/math/transform.h"

#include "game/common/voxel/voxel_group.h"
#include "game/common/world/world.h"

#include <set>

namespace Game
{

class Entity;

class WorldChunk : public VoxelGroup, public Core::Transform, public std::mutex
{
public:
	static unsigned int s_sideLength;

protected:
	glm::ivec3 m_chunkPosition;

	// The top/bottom-most block for a given position
	Core::Container2D< glm::ivec2 > m_yLevelLimits;

	World& m_world;

public:
	WorldChunk( World& world, const glm::ivec3& chunkPosition = glm::ivec3{ 0, 0, 0 } );

	const glm::ivec3& getChunkPosition() const;
	void setChunkPosition( const glm::ivec3& chunkPosition );

	const glm::ivec3 getWorldPosition() const;

	unsigned int getSideLength();

	World& getWorld() const;
	Core::Container2D< glm::ivec2 >& getYLevelLimits();

	void serialize( std::ostream& out ) const override;
	void deserialize( std::istream& in ) override;
};

} // namespace Game

#endif
