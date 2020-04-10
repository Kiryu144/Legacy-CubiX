/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_GENERATOR_H
#define CUBIX_WORLD_GENERATOR_H

#include "game/common/voxel/voxel.h"
#include "game/common/world/world.h"

#include <glm/vec2.hpp>

namespace Game
{

class WorldGenerator
{
public:
	struct Tree
	{
		std::shared_ptr< VoxelGroup > tree;
	};

protected:
	virtual void setVoxel( Voxel& voxel, unsigned int blocksUnderground );
	virtual Voxel getWaterVoxel();
	virtual int getHeight( const glm::ivec2& worldPosition );
	virtual void prepareForChunk( const glm::ivec3& chunkPosition ) {}

	std::vector<Tree> m_trees;
public:
	WorldGenerator() = default;

	void generateHeight( WorldChunk& chunk );
	void populate( WorldChunk& chunk );

	void addTree(std::shared_ptr<VoxelGroup>& tree);

	int getSeed()
	{
		return 1234;
	}
};

} // namespace Game

#endif
