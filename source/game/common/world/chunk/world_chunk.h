/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_H
#define CUBIX_WORLD_CHUNK_H

#include "core/cubix_macro.h"
#include "core/data/multiple_facing.h"

#include "game/common/voxel/voxel.h"
#include "game/common/world/chunk/i_world_chunk.h"

namespace Game
{

class World;
class Entity;

class WorldChunk : public IWorldChunk
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

protected:
	World& m_world;

	std::array< Voxel, IWorldChunk::GetVolume() > m_data;
	glm::ivec3 m_chunkPosition;
	State m_chunkState{ State::NEW };

	std::atomic_bool m_isGenerated{ false };
	std::atomic_bool m_isPopulated{ false };

	int m_millisecondsNotSeen{ 0 };

public:
	WorldChunk( World& world, const glm::ivec3& chunkPosition = glm::ivec3{ 0, 0, 0 } );

	CUBIX_GET_SET_CR_CR( m_chunkState, ChunkState );

	void setVoxel( const glm::uvec3& position, const Voxel& voxel ) override;
	const Voxel& getVoxel( const glm::uvec3& position ) const override;
	Voxel getVoxelFromWorld( const glm::ivec3& position,
							 const Voxel& _def = Voxel() ) const override;

	World& getWorld() const override;
	const glm::ivec3& getChunkPosition() const override;

	bool isPopulated() const override;
	bool isGenerated() const override;
	void setPopulated() override;
	void setGenerated() override;
	void setMillisecondsNotSeen( int ms ) override;
	int getMillisecondsNotSeen() override;
};

} // namespace Game

#endif
