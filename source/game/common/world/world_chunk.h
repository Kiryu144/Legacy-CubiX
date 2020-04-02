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

	double m_millisecondsNotSeen{ 0 };
	bool m_terrainGenerated{ false };
	bool m_terrainPopulated{ false };
	bool m_allowDrawing{ false };

	// The top/bottom-most block for a given position
	Core::Container2D< glm::ivec2 > m_yLevelLimits;

	World& m_world;

public:
	WorldChunk( World& world, const glm::ivec3& chunkPosition = glm::ivec3{ 0, 0, 0 } );

	CUBIX_GET_SET_R_CR( m_chunkPosition, ChunkPosition );
	CUBIX_GET_SET_R_CR( m_millisecondsNotSeen, MillisecondsNotSeen );
	CUBIX_GET_SET_CR_CR( m_terrainGenerated, TerrainGenerated );
	CUBIX_GET_SET_CR_CR( m_terrainPopulated, TerrainPopulated );
	CUBIX_GET_SET_CR_CR( m_allowDrawing, AllowDrawing );

	const glm::ivec3 getWorldPosition() const;

	unsigned int getSideLength();

	World& getWorld() const;
	Core::Container2D< glm::ivec2 >& getYLevelLimits();

	void serialize( std::ostream& out ) const override;
	void deserialize( std::istream& in ) override;
};

} // namespace Game

#endif
