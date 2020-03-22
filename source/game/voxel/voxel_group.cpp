/*
 * Copyright (c) 2020 David Klostermann.
 */

#include <cmath>
#include "voxel_group.h"

namespace Game
{

VoxelGroup::VoxelGroup( const glm::uvec3& size )
	: Core::Container3D< Voxel >( size ),
	  m_vertices( GL_ARRAY_BUFFER, Core::StandardVertexAttribute ),
	  m_normals( GL_ARRAY_BUFFER, Core::StandardNormalAttribute ),
	  m_colors( GL_ARRAY_BUFFER, Core::StandardColorByteAttribute )
{
}

void VoxelGroup::set( const glm::uvec3& pos, const Voxel& voxel, bool update )
{
	operator[]( pos ) = voxel;
	if( update )
	{
		VoxelGroup::updateFace( pos );
	}
}

Voxel& VoxelGroup::get( const glm::uvec3& pos )
{
	return operator[]( pos );
}

const Voxel& VoxelGroup::get( const glm::uvec3& pos ) const
{
	return operator[]( pos );
}

Core::Facing VoxelGroup::findVisibleFaces( const glm::uvec3& pos ) const
{
	using namespace Core;
	Facing facing;
	facing.setFace( Facing::LEFT,
					( pos.x >= m_size.x - 1 || get( pos + glm::uvec3{ 1, 0, 0 } ).a < 255 ) );
	facing.setFace( Facing::BACK,
					( pos.z >= m_size.z - 1 || get( pos + glm::uvec3{ 0, 0, 1 } ).a < 255 ) );
	facing.setFace( Facing::BOTTOM,
					( pos.y >= m_size.y - 1 || get( pos + glm::uvec3{ 0, 1, 0 } ).a < 255 ) );
	facing.setFace( Facing::RIGHT, ( pos.x <= 0 || get( pos + glm::uvec3{ -1, 0, 0 } ).a < 255 ) );
	facing.setFace( Facing::FRONT, ( pos.z <= 0 || get( pos + glm::uvec3{ 0, 0, -1 } ).a < 255 ) );
	facing.setFace( Facing::TOP, ( pos.y <= 0 || get( pos + glm::uvec3{ 0, -1, 0 } ).a < 255 ) );
	return facing;
}

void VoxelGroup::updateFace( const glm::uvec3& pos )
{
	get( pos ).getFacing() = findVisibleFaces( pos );
}

void VoxelGroup::updateAllFaces()
{
	for( int x = 0; x < m_size.x; ++x )
	{
		for( int y = 0; y < m_size.y; ++y )
		{
			for( int z = 0; z < m_size.z; ++z )
			{
				operator[]( { x, y, z } ).getFacing() = findVisibleFaces( { x, y, z } );
			}
		}
	}
}

void VoxelGroup::regenerateMesh()
{
	static const glm::vec3 s_vertices[ 6 * 6 ]{
		glm::vec3( 0.0, 0.0, 0.0 ), glm::vec3( 0.0, 1.0, 0.0 ), glm::vec3( 1.0, 0.0, 0.0 ),
		glm::vec3( 1.0, 0.0, 0.0 ), glm::vec3( 0.0, 1.0, 0.0 ), glm::vec3( 1.0, 1.0, 0.0 ),
		glm::vec3( 0.0, 0.0, 0.0 ), glm::vec3( 0.0, 0.0, 1.0 ), glm::vec3( 0.0, 1.0, 0.0 ),
		glm::vec3( 0.0, 1.0, 0.0 ), glm::vec3( 0.0, 0.0, 1.0 ), glm::vec3( 0.0, 1.0, 1.0 ),
		glm::vec3( 0.0, 0.0, 1.0 ), glm::vec3( 1.0, 0.0, 1.0 ), glm::vec3( 1.0, 1.0, 1.0 ),
		glm::vec3( 1.0, 1.0, 1.0 ), glm::vec3( 0.0, 1.0, 1.0 ), glm::vec3( 0.0, 0.0, 1.0 ),
		glm::vec3( 1.0, 0.0, 0.0 ), glm::vec3( 1.0, 1.0, 0.0 ), glm::vec3( 1.0, 0.0, 1.0 ),
		glm::vec3( 1.0, 0.0, 1.0 ), glm::vec3( 1.0, 1.0, 0.0 ), glm::vec3( 1.0, 1.0, 1.0 ),
		glm::vec3( 0.0, 0.0, 0.0 ), glm::vec3( 1.0, 0.0, 0.0 ), glm::vec3( 1.0, 0.0, 1.0 ),
		glm::vec3( 1.0, 0.0, 1.0 ), glm::vec3( 0.0, 0.0, 1.0 ), glm::vec3( 0.0, 0.0, 0.0 ),
		glm::vec3( 0.0, 1.0, 0.0 ), glm::vec3( 0.0, 1.0, 1.0 ), glm::vec3( 1.0, 1.0, 0.0 ),
		glm::vec3( 1.0, 1.0, 0.0 ), glm::vec3( 0.0, 1.0, 1.0 ), glm::vec3( 1.0, 1.0, 1.0 ),
	};

	static const glm::vec3 s_normals[ 6 ]{
		glm::vec3( 0.0, 0.0, -1.0 ), glm::vec3( -1.0, 0.0, 0.0 ), glm::vec3( 0.0, 0.0, 1.0 ),
		glm::vec3( 1.0, 0.0, 0.0 ),	 glm::vec3( 0.0, 1.0, 0.0 ),  glm::vec3( 0.0, -1.0, 0.0 )
	};

	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec3 > normals;
	std::vector< glm::tvec4< unsigned char > > colors;

	vertices.reserve( m_size.x * m_size.y * m_size.z );
	normals.reserve( m_size.x * m_size.y * m_size.z );
	colors.reserve( m_size.x * m_size.y * m_size.z );

	for( int x = 0; x < m_size.x; ++x )
	{
		for( int y = 0; y < m_size.y; ++y )
		{
			for( int z = 0; z < m_size.z; ++z )
			{
				const Voxel& voxel = operator[]( { x, y, z } );
				if( voxel.a == 0 )
				{
					continue;
				}

				const Core::Facing& visible = voxel.getFacing();
				// MultipleFacingData<uint8_t> light = voxel.getLightLevel();
				for( int i = 0; i < 6; ++i )
				{
					if( visible.hasFace( static_cast< Core::Facing::Face >( pow( 2.0, i ) ) ) )
					{
						// float lightMul = light.getFace(i) / 255.0f;
						for( int j = 0; j < 6; ++j )
						{
							vertices.push_back( s_vertices[ i * 6 + j ] + glm::vec3( x, y, z ) );
							normals.push_back( s_normals[ i ] );
							colors.push_back( voxel );
						}
					}
				}
			}
		}
	}

	m_vertices.upload< glm::vec3 >( &vertices[ 0 ], vertices.size() );
	m_normals.upload< glm::vec3 >( &normals[ 0 ], normals.size() );
	m_colors.upload< glm::tvec4< unsigned char > >( &colors[ 0 ], colors.size() );
}

Core::AttributeBuffer& VoxelGroup::getVertices()
{
	return m_vertices;
}

Core::AttributeBuffer& VoxelGroup::getNormals()
{
	return m_normals;
}

Core::AttributeBuffer& VoxelGroup::getColors()
{
	return m_colors;
}

} // namespace Game
