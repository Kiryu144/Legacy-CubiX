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

	struct Vertice
	{
		glm::vec3 m_position;
		glm::vec3 m_normal;
		Core::Color m_color;
	};

	std::vector< Vertice > m_verticeBuffer;
	bool m_upload{ false };
	size_t m_voxelCount{ 0 };

	void serialize( std::ostream& out ) const override;
	void deserialize( std::istream& in ) override;

public:
	VoxelGroup( const glm::uvec3& size );
	VoxelGroup( const std::string& voxFilePath );

	CUBIX_GET_V( m_voxelCount, VoxelCount );

	void set( const glm::uvec3& pos, const Voxel& voxel );
	Voxel& get( const glm::uvec3& pos );
	const Voxel& get( const glm::uvec3& pos ) const;

	Voxel getSafe( const glm::ivec3& pos, const Voxel& _default = Voxel() );
	const Voxel getSafe( const glm::ivec3& pos, const Voxel& _default = Voxel() ) const;

	void insert( const VoxelGroup& other, const glm::ivec3& position );

	Core::Facing findVisibleFaces( const glm::uvec3& pos ) const;

	void regenerateMesh();
	void upload();

	Core::AttributeBuffer& getVertices();
};

} // namespace Game

#endif
