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

class VoxelGroup : protected Core::Container3D< Voxel >
{
private:
	Core::AttributeBuffer m_vertices;
	Core::AttributeBuffer m_normals;
	Core::AttributeBuffer m_colors;

public:
	VoxelGroup( const glm::uvec3& size );
	VoxelGroup( const std::string& voxFilePath );

	void set( const glm::uvec3& pos, const Voxel& voxel, bool update = true );
	Voxel& get( const glm::uvec3& pos );
	const Voxel& get( const glm::uvec3& pos ) const;

	Core::Facing findVisibleFaces( const glm::uvec3& pos ) const;

	void updateFace( const glm::uvec3& pos );
	void updateAllFaces();
	void regenerateMesh();

	Core::AttributeBuffer& getVertices();
	Core::AttributeBuffer& getNormals();
	Core::AttributeBuffer& getColors();
};

} // namespace Game

#endif
