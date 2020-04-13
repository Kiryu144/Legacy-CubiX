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
	static const glm::vec3& GetPosForCube( const Core::MultipleFacing::Face& face, int index );
	static const glm::vec3& GetNormForCube( const Core::MultipleFacing::Face& face );
	int getACColorCorrectionForCube( const Core::MultipleFacing::Face& face,
									 const glm::ivec3& pos,
									 int index );

protected:
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		Core::Color color;
	};

	// Vertices ready to be uploaded to the GPU if m_uploadVertices == true
	std::vector< Vertex > m_vertexBuffer;
	bool m_uploadVertices{ false };

	Core::AttributeBuffer m_attributeBuffer;

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

	Core::MultipleFacing findVisibleFaces( const glm::uvec3& pos ) const;

	void regenerateMesh();
	void upload();

	Core::AttributeBuffer& getVertexAttribute();
};

} // namespace Game

#endif
