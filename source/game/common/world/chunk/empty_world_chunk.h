/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_EMPTY_WORLD_CHUNK_H
#define CUBIX_EMPTY_WORLD_CHUNK_H

#include "game/common/world/chunk/i_world_chunk.h"

namespace Game
{

class EmptyWorldChunk : public IWorldChunk
{
protected:
	World& m_world;
	glm::ivec3 m_chunkPosition;

	int m_millisecondsNotSeen{ 0 };

public:
	EmptyWorldChunk( World& world, const glm::ivec3& chunkPosition );

	void setVoxel( const glm::uvec3& position, const Voxel& voxel ) override;
	const Voxel& getVoxel( const glm::uvec3& position ) const override;
	World& getWorld() const override;
	const glm::ivec3& getChunkPosition() const override;
	Voxel getVoxelFromWorld( const glm::ivec3& position, const Voxel& _def ) const override;
	bool isPopulated() const override;
	bool isGenerated() const override;
	void setPopulated() override {}
	void setGenerated() override {}
	void setMillisecondsNotSeen( int ms ) override;
	int getMillisecondsNotSeen() override;
	size_t getVoxelCount() override;
};

} // namespace Game

#endif
