/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_VOXEL_CLIPBOARD_H
#define CUBIX_VOXEL_CLIPBOARD_H

#include "game/common/voxel/voxel_group.h"

#include <memory>

namespace Game
{

class VoxelClipboard
{
protected:
	std::unique_ptr< VoxelGroup > m_voxelGroup;

public:
	void createSphere( unsigned int radius, const Voxel& voxel );
	void createCube( unsigned int sideLength, const Voxel& voxel );

	CUBIX_GET_CR( m_voxelGroup, VoxelGroup );
};

} // namespace Game

#endif
