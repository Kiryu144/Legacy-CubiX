/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_VOXEL_GROUP_H
#define CUBIX_VOXEL_GROUP_H

#include "voxel.h"

#include "core/data/container3d.h"
#include "core/opengl/attributebuffer.h"

namespace Game
{

class VoxelGroup : public Core::Container3D< Voxel >
{
protected:
	Core::AttributeBuffer m_vertices;
	Core::AttributeBuffer m_normals;
	Core::AttributeBuffer m_colors;

	std::vector< glm::vec3 > m_verticeBuffer;
	std::vector< glm::vec3 > m_normalBuffer;
	std::vector< glm::tvec4< unsigned char > > m_colorBuffer;

	void serialize( std::ostream& out ) const override;
	void deserialize( std::istream& in ) override;

public:
	VoxelGroup( const glm::uvec3& size );
	VoxelGroup( const std::string& voxFilePath );

	void set( const glm::uvec3& pos, const Voxel& voxel );
	Voxel& get( const glm::uvec3& pos );
	const Voxel& get( const glm::uvec3& pos ) const;

	Core::Facing findVisibleFaces( const glm::uvec3& pos ) const;

	void regenerateMesh();
	void upload();

	Core::AttributeBuffer& getVertices();
	Core::AttributeBuffer& getNormals();
	Core::AttributeBuffer& getColors();
};

} // namespace Game

#endif
