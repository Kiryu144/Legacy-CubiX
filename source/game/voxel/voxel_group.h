/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_VOXEL_GROUP_H
#define CUBIX_VOXEL_GROUP_H

#include "core/container/container3d.h"
#include "core/opengl/attributebuffer.h"
#include "game/voxel/voxel.h"

namespace Game
{

class VoxelGroup : public Core::Container3D< FlagVoxel >
{
private:
	Core::AttributeBuffer m_vertices;
	Core::AttributeBuffer m_normals;
	Core::AttributeBuffer m_colors;

public:
	VoxelGroup( const glm::uvec3& size );

	void generateMesh();

	Core::AttributeBuffer& getVertices();
	Core::AttributeBuffer& getNormals();
	Core::AttributeBuffer& getColors();
};

} // namespace Game

#endif
