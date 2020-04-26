/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_H
#define CUBIX_WORLD_CHUNK_H

#include "empty_world_chunk.h"

#include "core/cubix_macro.h"
#include "core/data/multiple_facing.h"

#include "game/world/voxel/voxel.h"

namespace Game
{

class World;
class Entity;

class WorldChunk : public EmptyWorldChunk
{
protected:
	std::array< Voxel, IWorldChunk::GetVolume() > m_data;
	size_t m_voxelCount{ 0 };

public:
	WorldChunk( World& world, const glm::ivec3& chunkPosition = glm::ivec3{ 0, 0, 0 } );

	void setVoxel( const glm::uvec3& position, const Voxel& voxel ) override;
	const Voxel& getVoxel( const glm::uvec3& position ) const override;
	Voxel getVoxelFromWorld( const glm::ivec3& position,
							 const Voxel& _def = Voxel() ) const override;

	size_t getVoxelCount() override;
};

} // namespace Game

#endif
