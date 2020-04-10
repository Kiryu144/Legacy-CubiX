/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_H
#define CUBIX_WORLD_CHUNK_H

#include "core/data/container2d.h"
#include "core/logic/memory.h"
#include "core/logic/serializeable.h"
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
	static glm::ivec3 WorldPosToChunkPos( const glm::vec3& worldPos )
	{
		return glm::ivec3{ std::floor( worldPos.x / s_sideLength ),
						   std::floor( worldPos.y / s_sideLength ),
						   std::floor( worldPos.z / s_sideLength ) };
	}

protected:
	glm::ivec3 m_chunkPosition;

	double m_millisecondsNotSeen{ 0 };
	bool m_terrainGenerated{ false };
	bool m_terrainPopulated{ false };
	bool m_meshGenerated{ false };

	World& m_world;

public:
	WorldChunk( World& world, const glm::ivec3& chunkPosition = glm::ivec3{ 0, 0, 0 } );

	CUBIX_GET_SET_R_CR( m_chunkPosition, ChunkPosition );
	CUBIX_GET_SET_R_CR( m_millisecondsNotSeen, MillisecondsNotSeen );
	CUBIX_GET_SET_CR_CR( m_terrainGenerated, TerrainGenerated );
	CUBIX_GET_SET_CR_CR( m_terrainPopulated, TerrainPopulated );
	CUBIX_GET_SET_CR_CR( m_meshGenerated, AllowDrawing );

	const glm::ivec3 getWorldPosition() const;

	unsigned int getSideLength();

	World& getWorld() const;

	void serialize( std::ostream& out ) const override;
	void deserialize( std::istream& in ) override;
};

} // namespace Game

#endif
