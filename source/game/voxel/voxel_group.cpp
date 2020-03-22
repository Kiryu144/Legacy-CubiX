/*
 * Copyright (c) 2020 David Klostermann.
 */

#include <cmath>
#include "voxel_group.h"

namespace Game
{

VoxelGroup::VoxelGroup( const glm::uvec3& size )
	: m_vertices( GL_ARRAY_BUFFER, Core::StandardVertexAttribute ),
	  m_normals( GL_ARRAY_BUFFER, Core::StandardNormalAttribute ),
	  m_colors( GL_ARRAY_BUFFER, Core::StandardColorAttribute ),
	  Container3D( size )
{
}

void VoxelGroup::generateMesh()
{
	auto& first = operator[]( { 0, 0, 0 } );
	if( !first.getFlag( FlagVoxel::Flag::FACE_FLAGS_SET ) )
	{
		first.setFlag( FlagVoxel::Flag::FACE_FLAGS_SET, true );

		for( int x = 0; x < m_size.x; ++x )
		{
			for( int y = 0; y < m_size.x; ++y )
			{
				for( int z = 0; z < m_size.x; ++z )
				{
					auto& v = operator[]( { 0, 0, 0 } );
					v.setFlag( FlagVoxel::Flag::FACE_FLAGS_SET, true );
					// clang-format off
					v.setFlag(FlagVoxel::Flag::FACE_NORTH, z >= m_size.z-1 || !operator[]({x, y, z+1}).getFlag(FlagVoxel::Flag::EXISTS));
					v.setFlag(FlagVoxel::Flag::FACE_EAST, x >= m_size.x-1 || !operator[]({x+1, y, z}).getFlag(FlagVoxel::Flag::EXISTS));
					v.setFlag(FlagVoxel::Flag::FACE_SOUTH, z <= 0 || !operator[]({x, y, z-1}).getFlag(FlagVoxel::Flag::EXISTS));
					v.setFlag(FlagVoxel::Flag::FACE_WEST, x <= 0 || !operator[]({x-1, y, z}).getFlag(FlagVoxel::Flag::EXISTS));
					v.setFlag(FlagVoxel::Flag::FACE_UP, y >= m_size.y-1 || !operator[]({x, y+1, z}).getFlag(FlagVoxel::Flag::EXISTS));
					v.setFlag(FlagVoxel::Flag::FACE_DOWN, y <= 0 || !operator[]({x, y-1, z}).getFlag(FlagVoxel::Flag::EXISTS));
					// clang-format on
				}
			}
		}
	}

	static const glm::vec3 s_vertices[ 6 * 7 ]{
		// clang-format off
		glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 0.0),
		glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 1.0),
		glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 1.0),
		glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 0.0), glm::vec3(1.0, 0.0, 1.0), glm::vec3(1.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 1.0), glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0),
		// clang-format on
	};

	static const glm::vec3 s_normals[ 6 ]{
		glm::vec3( 0.0, 0.0, -1.0 ), glm::vec3( -1.0, 0.0, 0.0 ), glm::vec3( 0.0, 0.0, 1.0 ),
		glm::vec3( 1.0, 0.0, 0.0 ),	 glm::vec3( 0.0, 1.0, 0.0 ),  glm::vec3( 0.0, -1.0, 0.0 )
	};

	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec3 > normals;
	std::vector< glm::vec4 > colors;

	vertices.reserve( m_size.x * m_size.y * m_size.z );
	normals.reserve( m_size.x * m_size.y * m_size.z );
	colors.reserve( m_size.x * m_size.y * m_size.z );

	for( int x = 0; x < m_size.x; ++x )
	{
		for( int y = 0; y < m_size.x; ++y )
		{
			for( int z = 0; z < m_size.x; ++z )
			{
				size_t index = getIndexForPosition( x, y, z );
				auto& v		 = m_data[ index ];
				if( !v.getFlag( FlagVoxel::Flag::EXISTS ) )
				{
					continue;
				}

				for( int i = 0; i < 6; ++i )
				{
					FlagVoxel::Flag side = FlagVoxel::Flag::FACE_NORTH;
					side = static_cast< FlagVoxel::Flag >( static_cast< uint64_t >( side )
														   + std::pow( 2.0, i ) );
					if( v.getFlag( side ) )
					{
						// float lightMul = light.getFace(i) / 255.0f;
						for( int j = 0; j < 6; ++j )
						{
							glm::vec3 vertice = s_vertices[ i * 6 + j ] + glm::vec3( x, -y, z );
							glm::vec3 normal  = s_normals[ i ];

							vertices.push_back( vertice );
							normals.push_back( normal );
							colors.push_back( v.toFloat() );
						}
					}
				}
			}
		}
	}

	if( vertices.empty() )
	{
		return;
	}

	m_vertices.upload< glm::vec3 >( &vertices.at( 0 ), vertices.size() );
	m_normals.upload< glm::vec3 >( &normals.at( 0 ), normals.size() );
	m_colors.upload< glm::vec4 >( &colors.at( 0 ), colors.size() );
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
