/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "render_world_chunk.h"

#include "core/opengl/data/interleaved_attribute.h"

namespace Game
{

RenderWorldChunk::RenderWorldChunk( World& world, const glm::ivec3& chunkPosition )
	: WorldChunk( world, chunkPosition ), m_attributeBuffer( Core::InterleavedVertNormColAttribute )
{
	m_position = IWorldChunk::WorldPosFromChunkPos( chunkPosition );
}

const glm::vec3& RenderWorldChunk::GetPosForCube( const Core::MultipleFacing::Face& face,
												  int index )
{
	static const glm::vec3 s_vertices[ 6 * 6 ]{
		glm::vec3( 1.0, 0.0, 0.0 ), glm::vec3( 0.0, 0.0, 0.0 ), glm::vec3( 1.0, 1.0, 0.0 ),
		glm::vec3( 0.0, 1.0, 0.0 ), glm::vec3( 1.0, 1.0, 0.0 ), glm::vec3( 0.0, 0.0, 0.0 ),

		glm::vec3( 0.0, 0.0, 0.0 ), glm::vec3( 0.0, 0.0, 1.0 ), glm::vec3( 0.0, 1.0, 0.0 ),
		glm::vec3( 0.0, 1.0, 1.0 ), glm::vec3( 0.0, 1.0, 0.0 ), glm::vec3( 0.0, 0.0, 1.0 ),

		glm::vec3( 0.0, 0.0, 1.0 ), glm::vec3( 1.0, 0.0, 1.0 ), glm::vec3( 0.0, 1.0, 1.0 ),
		glm::vec3( 1.0, 1.0, 1.0 ), glm::vec3( 0.0, 1.0, 1.0 ), glm::vec3( 1.0, 0.0, 1.0 ),

		glm::vec3( 1.0, 0.0, 1.0 ), glm::vec3( 1.0, 0.0, 0.0 ), glm::vec3( 1.0, 1.0, 1.0 ),
		glm::vec3( 1.0, 1.0, 0.0 ), glm::vec3( 1.0, 1.0, 1.0 ), glm::vec3( 1.0, 0.0, 0.0 ),

		glm::vec3( 0.0, 0.0, 0.0 ), glm::vec3( 1.0, 0.0, 0.0 ), glm::vec3( 1.0, 0.0, 1.0 ),
		glm::vec3( 1.0, 0.0, 1.0 ), glm::vec3( 0.0, 0.0, 1.0 ), glm::vec3( 0.0, 0.0, 0.0 ),

		glm::vec3( 0.0, 1.0, 0.0 ), glm::vec3( 0.0, 1.0, 1.0 ), glm::vec3( 1.0, 1.0, 0.0 ),
		glm::vec3( 1.0, 1.0, 0.0 ), glm::vec3( 0.0, 1.0, 1.0 ), glm::vec3( 1.0, 1.0, 1.0 ),
	};
	return s_vertices[ Core::MultipleFacing::IndexOf( face ) * 6 + index ];
}

const glm::vec3& RenderWorldChunk::GetNormForCube( const Core::MultipleFacing::Face& face )
{
	static const glm::vec3 s_normals[ 6 ]{
		glm::vec3( 0.0, 0.0, -1.0 ), glm::vec3( -1.0, 0.0, 0.0 ), glm::vec3( 0.0, 0.0, 1.0 ),
		glm::vec3( 1.0, 0.0, 0.0 ),	 glm::vec3( 0.0, 1.0, 0.0 ),  glm::vec3( 0.0, -1.0, 0.0 )
	};
	return s_normals[ Core::MultipleFacing::IndexOf( face ) ];
}

int RenderWorldChunk::getACColorCorrectionForCube( const Core::MultipleFacing::Face& face,
												   const glm::ivec3& pos,
												   int index )
{
	static const glm::ivec3 s_acLookups[ 6 * 6 * 3 ]{
		{ 1, 0, -1 },  { 1, -1, -1 },  { 0, -1, -1 }, { 0, -1, -1 }, { -1, -1, -1 }, { -1, 0, -1 },
		{ 1, 0, -1 },  { 1, 1, -1 },   { 0, 1, -1 },  { 0, 1, -1 },	 { -1, 1, -1 },	 { -1, 0, -1 },
		{ 1, 0, -1 },  { 1, 1, -1 },   { 0, 1, -1 },  { 0, -1, -1 }, { -1, -1, -1 }, { -1, 0, -1 },

		{ -1, 0, -1 }, { -1, -1, -1 }, { -1, -1, 0 }, { -1, -1, 0 }, { -1, -1, 1 },	 { -1, 0, 1 },
		{ -1, 0, -1 }, { -1, 1, -1 },  { -1, 1, 0 },  { -1, 1, 0 },	 { -1, 1, 1 },	 { -1, 0, 1 },
		{ -1, 0, -1 }, { -1, 1, -1 },  { -1, 1, 0 },  { -1, -1, 0 }, { -1, -1, 1 },	 { -1, 0, 1 },

		{ -1, 0, 1 },  { -1, -1, 1 },  { 0, -1, 1 },  { 0, -1, 1 },	 { 1, -1, 1 },	 { 1, 0, 1 },
		{ -1, 0, 1 },  { -1, 1, 1 },   { 0, 1, 1 },	  { 0, 1, 1 },	 { 1, 1, 1 },	 { 1, 0, 1 },
		{ -1, 0, 1 },  { -1, 1, 1 },   { 0, 1, 1 },	  { 0, -1, 1 },	 { 1, -1, 1 },	 { 1, 0, 1 },

		{ 1, 0, 1 },   { 1, -1, 1 },   { 1, -1, 0 },  { 1, -1, 0 },	 { 1, -1, -1 },	 { 1, 0, -1 },
		{ 1, 0, 1 },   { 1, 1, 1 },	   { 1, 1, 0 },	  { 1, 1, 0 },	 { 1, 1, -1 },	 { 1, 0, -1 },
		{ 1, 0, 1 },   { 1, 1, 1 },	   { 1, 1, 0 },	  { 1, -1, 0 },	 { 1, -1, -1 },	 { 1, 0, -1 },

		{ 0, -1, -1 }, { -1, -1, -1 }, { -1, -1, 0 }, { 1, -1, 0 },	 { 1, -1, -1 },	 { 0, -1, -1 },
		{ 0, -1, 1 },  { 1, -1, 1 },   { 1, -1, 0 },  { 0, -1, 1 },	 { 1, -1, 1 },	 { 1, -1, 0 },
		{ 0, -1, 1 },  { -1, -1, 1 },  { -1, -1, 0 }, { 0, -1, -1 }, { -1, -1, -1 }, { -1, -1, 0 },

		{ 0, 1, -1 },  { -1, 1, -1 },  { -1, 1, 0 },  { -1, 1, 0 },	 { -1, 1, 1 },	 { 0, 1, 1 },
		{ 1, 1, 0 },   { 1, 1, -1 },   { 0, 1, -1 },  { 1, 1, 0 },	 { 1, 1, -1 },	 { 0, 1, -1 },
		{ -1, 1, 0 },  { -1, 1, 1 },   { 0, 1, 1 },	  { 1, 1, 0 },	 { 1, 1, 1 },	 { 0, 1, 1 },
	};
	const int& i{ static_cast< const int& >( Core::MultipleFacing::IndexOf( face ) * 18
											 + index * 3 ) };
	bool side1	= getVoxelFromWorld( pos + s_acLookups[ i + 0 ] ).exists();
	bool corner = getVoxelFromWorld( pos + s_acLookups[ i + 1 ] ).exists();
	bool side2	= getVoxelFromWorld( pos + s_acLookups[ i + 2 ] ).exists();
	return ( side1 && side2 ) ? 3 : side1 + side2 + corner;
}

void RenderWorldChunk::regenerateMesh()
{
	{
		std::lock_guard< decltype( m_uploadMutex ) > lock_guard( m_uploadMutex );
		m_upload = false;
	}

	m_vertices.clear();
	m_vertices.reserve( GetVolume() * 36 );
	for( int x = 0; x < GetSideLength(); ++x )
	{
		for( int y = 0; y < GetSideLength(); ++y )
		{
			for( int z = 0; z < GetSideLength(); ++z )
			{
				const glm::ivec3 pos{ x, y, z };
				const Voxel voxel{ getVoxel( pos ) };
				if( voxel.a == 0 )
				{
					continue;
				}

				const auto& visibleFaces{ findVisibleFaces( pos ) };
				for( const auto& face : Core::MultipleFacing::Facings )
				{
					if( !visibleFaces.hasFace( face ) )
					{
						continue;
					}
					Vertex vertex;
					for( int vertice = 0; vertice < 6; ++vertice )
					{
						vertex.color	= voxel;
						vertex.position = glm::vec3( pos ) + GetPosForCube( face, vertice );
						vertex.normal	= GetNormForCube( face );
						int acDarkness	= getACColorCorrectionForCube( face, pos, vertice );
						vertex.color.add( -acDarkness, -acDarkness, -acDarkness );
						m_vertices.push_back( vertex );
					}
				}
			}
		}
	}

	{
		std::lock_guard< decltype( m_uploadMutex ) > lock_guard( m_uploadMutex );
		m_upload = true;
	}
}

Core::MultipleFacing RenderWorldChunk::findVisibleFaces( const glm::uvec3& pos ) const
{
	using namespace Core;
	glm::ivec3 ipos{ pos };
	MultipleFacing facing;
	facing.setFace( MultipleFacing::LEFT,
					getVoxelFromWorld( ipos + glm::ivec3{ 1, 0, 0 } ).a < 255 );
	facing.setFace( MultipleFacing::BACK,
					getVoxelFromWorld( ipos + glm::ivec3{ 0, 0, 1 } ).a < 255 );
	facing.setFace( MultipleFacing::BOTTOM,
					getVoxelFromWorld( ipos + glm::ivec3{ 0, 1, 0 } ).a < 255 );
	facing.setFace( MultipleFacing::RIGHT,
					getVoxelFromWorld( ipos + glm::ivec3{ -1, 0, 0 } ).a < 255 );
	facing.setFace( MultipleFacing::FRONT,
					getVoxelFromWorld( ipos + glm::ivec3{ 0, 0, -1 } ).a < 255 );
	facing.setFace( MultipleFacing::TOP,
					getVoxelFromWorld( ipos + glm::ivec3{ 0, -1, 0 } ).a < 255 );
	return facing;
}

void RenderWorldChunk::uploadWhenNeeded()
{
	std::lock_guard< decltype( m_uploadMutex ) > guard( m_uploadMutex );
	if( m_upload )
	{
		if( !m_vertices.empty() )
		{
			m_attributeBuffer.upload( &m_vertices.at( 0 ), m_vertices.size() );
		}

		m_vertices.clear();
		m_upload = false;
	}
}

bool RenderWorldChunk::isMeshGenerated() const
{
	return m_meshGenerated;
}

void RenderWorldChunk::setMeshGenerated()
{
	m_meshGenerated = true;
}

} // namespace Game