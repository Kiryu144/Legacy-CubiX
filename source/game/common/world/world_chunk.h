/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_H
#define CUBIX_WORLD_CHUNK_H

#include "core/data/memory.h"
#include "core/data/serializeable.h"
#include "core/math/transform.h"

#include "game/common/voxel/voxel_group.h"

#include <set>

namespace Game
{

class Entity;

class WorldChunk : public VoxelGroup, public Core::Transform, public std::mutex
{
public:
	static unsigned int s_sideLength;
	glm::ivec3 m_chunkPosition;

public:
	WorldChunk( const glm::ivec3& chunkPosition = { 0, 0, 0 } );

	const glm::ivec3& getChunkPosition() const;
	void setChunkPosition( const glm::ivec3& chunkPosition );

	unsigned int getSideLength();

	void serialize( std::ostream& out ) const override;
	void deserialize( std::istream& in ) override;
};

} // namespace Game

#endif
