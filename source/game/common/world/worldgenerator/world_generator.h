/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_GENERATOR_H
#define CUBIX_WORLD_GENERATOR_H

#include "game/common/world/voxel/voxel.h"
#include "game/common/world/world.h"

#include <glm/vec2.hpp>

namespace Game
{

class VoxelGroup;

class WorldGenerator
{
public:
	struct Tree
	{
		std::shared_ptr< VoxelGroup > tree;
	};

protected:
	virtual Voxel getVoxel( unsigned int blocksUnderground, int yLevel ) const;
	virtual Voxel getWaterVoxel() const;
	virtual int getHeight( const glm::ivec2& worldPosition ) const;
	virtual void prepareForChunk( const glm::ivec3& chunkPosition ) {}

	std::vector< Tree > m_trees;

public:
	WorldGenerator() = default;

	void generateHeight( std::shared_ptr< IWorldChunk > chunk );
	void populate( std::shared_ptr< IWorldChunk > chunk );

	void addTree( std::shared_ptr< VoxelGroup >& tree );

	int getSeed() const
	{
		return 123555;
	}
};

} // namespace Game

#endif
