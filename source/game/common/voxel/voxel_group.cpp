/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "voxel_group.h"

#include <cmath>

#include "core/io/riff_parser.h"

namespace Game
{

VoxelGroup::VoxelGroup( const glm::uvec3& size )
	: Core::Container3D< Voxel >( size ),
	  m_vertices( GL_ARRAY_BUFFER, Core::StandardVertexAttribute ),
	  m_normals( GL_ARRAY_BUFFER, Core::StandardNormalAttribute ),
	  m_colors( GL_ARRAY_BUFFER, Core::StandardColorByteAttribute )
{
}

VoxelGroup::VoxelGroup( const std::string& voxFilePath )
	: Core::Container3D< Voxel >( { 1, 1, 1 } ),
	  m_vertices( GL_ARRAY_BUFFER, Core::StandardVertexAttribute ),
	  m_normals( GL_ARRAY_BUFFER, Core::StandardNormalAttribute ),
	  m_colors( GL_ARRAY_BUFFER, Core::StandardColorByteAttribute )
{
	Core::RiffParser vox( voxFilePath );

	Core::RiffParser::Byte* size = vox.getMain().children.at( "SIZE" ).data;
	Core::RiffParser::Byte* xyzi = vox.getMain().children.at( "XYZI" ).data;

	// Read SIZE
	glm::uvec3 dimensions;
	dimensions.x = ( *reinterpret_cast< uint32_t* >( size + 0 ) );
	dimensions.y = ( *reinterpret_cast< uint32_t* >( size + 4 ) );
	dimensions.z = ( *reinterpret_cast< uint32_t* >( size + 8 ) );

	initialize( dimensions );

	std::vector< int > palette;

	// Read RGBA
	if( vox.getMain().children.find( "RGBA" ) != vox.getMain().children.end() )
	{
		Core::RiffParser::Byte* rgba = vox.getMain().children.at( "RGBA" ).data;
		palette.resize( 1024 );
		for( int i = 0; i < 1024; ++i )
		{
			palette[ i ] = int( *reinterpret_cast< uint8_t* >( rgba + i ) );
		}
	}
	else
	{
		// TODO: Optimize, don't trust the compiler.
		palette = std::vector< int >{
			0,	 0,	  0,   0,	255, 255, 255, 255, 255, 204, 255, 255, 255, 153, 255, 255, 255,
			102, 255, 255, 255, 51,	 255, 255, 255, 0,	 255, 255, 255, 255, 204, 255, 255, 204,
			204, 255, 255, 153, 204, 255, 255, 102, 204, 255, 255, 51,	204, 255, 255, 0,	204,
			255, 255, 255, 153, 255, 255, 204, 153, 255, 255, 153, 153, 255, 255, 102, 153, 255,
			255, 51,  153, 255, 255, 0,	  153, 255, 255, 255, 102, 255, 255, 204, 102, 255, 255,
			153, 102, 255, 255, 102, 102, 255, 255, 51,	 102, 255, 255, 0,	 102, 255, 255, 255,
			51,	 255, 255, 204, 51,	 255, 255, 153, 51,	 255, 255, 102, 51,	 255, 255, 51,	51,
			255, 255, 0,   51,	255, 255, 255, 0,	255, 255, 204, 0,	255, 255, 153, 0,	255,
			255, 102, 0,   255, 255, 51,  0,   255, 255, 0,	  0,   255, 255, 255, 255, 204, 255,
			204, 255, 204, 255, 153, 255, 204, 255, 102, 255, 204, 255, 51,	 255, 204, 255, 0,
			255, 204, 255, 255, 204, 204, 255, 204, 204, 204, 255, 153, 204, 204, 255, 102, 204,
			204, 255, 51,  204, 204, 255, 0,   204, 204, 255, 255, 153, 204, 255, 204, 153, 204,
			255, 153, 153, 204, 255, 102, 153, 204, 255, 51,  153, 204, 255, 0,	  153, 204, 255,
			255, 102, 204, 255, 204, 102, 204, 255, 153, 102, 204, 255, 102, 102, 204, 255, 51,
			102, 204, 255, 0,	102, 204, 255, 255, 51,	 204, 255, 204, 51,	 204, 255, 153, 51,
			204, 255, 102, 51,	204, 255, 51,  51,	204, 255, 0,   51,	204, 255, 255, 0,	204,
			255, 204, 0,   204, 255, 153, 0,   204, 255, 102, 0,   204, 255, 51,  0,   204, 255,
			0,	 0,	  204, 255, 255, 255, 153, 255, 204, 255, 153, 255, 153, 255, 153, 255, 102,
			255, 153, 255, 51,	255, 153, 255, 0,	255, 153, 255, 255, 204, 153, 255, 204, 204,
			153, 255, 153, 204, 153, 255, 102, 204, 153, 255, 51,  204, 153, 255, 0,   204, 153,
			255, 255, 153, 153, 255, 204, 153, 153, 255, 153, 153, 153, 255, 102, 153, 153, 255,
			51,	 153, 153, 255, 0,	 153, 153, 255, 255, 102, 153, 255, 204, 102, 153, 255, 153,
			102, 153, 255, 102, 102, 153, 255, 51,	102, 153, 255, 0,	102, 153, 255, 255, 51,
			153, 255, 204, 51,	153, 255, 153, 51,	153, 255, 102, 51,	153, 255, 51,  51,	153,
			255, 0,	  51,  153, 255, 255, 0,   153, 255, 204, 0,   153, 255, 153, 0,   153, 255,
			102, 0,	  153, 255, 51,	 0,	  153, 255, 0,	 0,	  153, 255, 255, 255, 102, 255, 204,
			255, 102, 255, 153, 255, 102, 255, 102, 255, 102, 255, 51,	255, 102, 255, 0,	255,
			102, 255, 255, 204, 102, 255, 204, 204, 102, 255, 153, 204, 102, 255, 102, 204, 102,
			255, 51,  204, 102, 255, 0,	  204, 102, 255, 255, 153, 102, 255, 204, 153, 102, 255,
			153, 153, 102, 255, 102, 153, 102, 255, 51,	 153, 102, 255, 0,	 153, 102, 255, 255,
			102, 102, 255, 204, 102, 102, 255, 153, 102, 102, 255, 102, 102, 102, 255, 51,	102,
			102, 255, 0,   102, 102, 255, 255, 51,	102, 255, 204, 51,	102, 255, 153, 51,	102,
			255, 102, 51,  102, 255, 51,  51,  102, 255, 0,	  51,  102, 255, 255, 0,   102, 255,
			204, 0,	  102, 255, 153, 0,	  102, 255, 102, 0,	  102, 255, 51,	 0,	  102, 255, 0,
			0,	 102, 255, 255, 255, 51,  255, 204, 255, 51,  255, 153, 255, 51,  255, 102, 255,
			51,	 255, 51,  255, 51,	 255, 0,   255, 51,	 255, 255, 204, 51,	 255, 204, 204, 51,
			255, 153, 204, 51,	255, 102, 204, 51,	255, 51,  204, 51,	255, 0,	  204, 51,	255,
			255, 153, 51,  255, 204, 153, 51,  255, 153, 153, 51,  255, 102, 153, 51,  255, 51,
			153, 51,  255, 0,	153, 51,  255, 255, 102, 51,  255, 204, 102, 51,  255, 153, 102,
			51,	 255, 102, 102, 51,	 255, 51,  102, 51,	 255, 0,   102, 51,	 255, 255, 51,	51,
			255, 204, 51,  51,	255, 153, 51,  51,	255, 102, 51,  51,	255, 51,  51,  51,	255,
			0,	 51,  51,  255, 255, 0,	  51,  255, 204, 0,	  51,  255, 153, 0,	  51,  255, 102,
			0,	 51,  255, 51,	0,	 51,  255, 0,	0,	 51,  255, 255, 255, 0,	  255, 204, 255,
			0,	 255, 153, 255, 0,	 255, 102, 255, 0,	 255, 51,  255, 0,	 255, 0,   255, 0,
			255, 255, 204, 0,	255, 204, 204, 0,	255, 153, 204, 0,	255, 102, 204, 0,	255,
			51,	 204, 0,   255, 0,	 204, 0,   255, 255, 153, 0,   255, 204, 153, 0,   255, 153,
			153, 0,	  255, 102, 153, 0,	  255, 51,	153, 0,	  255, 0,	153, 0,	  255, 255, 102,
			0,	 255, 204, 102, 0,	 255, 153, 102, 0,	 255, 102, 102, 0,	 255, 51,  102, 0,
			255, 0,	  102, 0,	255, 255, 51,  0,	255, 204, 51,  0,	255, 153, 51,  0,	255,
			102, 51,  0,   255, 51,	 51,  0,   255, 0,	 51,  0,   255, 255, 0,	  0,   255, 204,
			0,	 0,	  255, 153, 0,	 0,	  255, 102, 0,	 0,	  255, 51,	0,	 0,	  255, 0,	0,
			238, 255, 0,   0,	221, 255, 0,   0,	187, 255, 0,   0,	170, 255, 0,   0,	136,
			255, 0,	  0,   119, 255, 0,	  0,   85,	255, 0,	  0,   68,	255, 0,	  0,   34,	255,
			0,	 0,	  17,  255, 0,	 238, 0,   255, 0,	 221, 0,   255, 0,	 187, 0,   255, 0,
			170, 0,	  255, 0,	136, 0,	  255, 0,	119, 0,	  255, 0,	85,	 0,	  255, 0,	68,
			0,	 255, 0,   34,	0,	 255, 0,   17,	0,	 255, 238, 0,	0,	 255, 221, 0,	0,
			255, 187, 0,   0,	255, 170, 0,   0,	255, 136, 0,   0,	255, 119, 0,   0,	255,
			85,	 0,	  0,   255, 68,	 0,	  0,   255, 34,	 0,	  0,   255, 17,	 0,	  0,   255, 238,
			238, 238, 255, 221, 221, 221, 255, 187, 187, 187, 255, 170, 170, 170, 255, 136, 136,
			136, 255, 119, 119, 119, 255, 85,  85,	85,	 255, 68,  68,	68,	 255, 34,  34,	34,
			255, 17,  17,  17
		};
	}

	// Read XYZI
	int numVoxels = *reinterpret_cast< uint32_t* >( xyzi + 0 );
	for( int n = 0; n < numVoxels; ++n )
	{
		glm::uvec3 pos;
		pos.x = *reinterpret_cast< int8_t* >( xyzi + 4 + ( n * 4 ) + 0 );
		pos.z = *reinterpret_cast< int8_t* >( xyzi + 4 + ( n * 4 ) + 1 );
		pos.y = *reinterpret_cast< int8_t* >( xyzi + 4 + ( n * 4 ) + 2 );
		Voxel voxel;
		int i	= int( *reinterpret_cast< uint8_t* >( xyzi + 4 + ( n * 4 ) + 3 ) ) - 1;
		voxel.r = palette[ ( i * 4 ) + 0 ];
		voxel.g = palette[ ( i * 4 ) + 1 ];
		voxel.b = palette[ ( i * 4 ) + 2 ];
		voxel.a = palette[ ( i * 4 ) + 3 ];
		set( pos, voxel, false );
	}
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

	glm::vec3 halfSize{ m_size.x * 0.5f, m_size.y * 0.5f, m_size.z * 0.5f };

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
							vertices.push_back(
								s_vertices[ i * 6 + j ]
								+ glm::vec3( x - halfSize.x, y - halfSize.y, z - halfSize.z ) );
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
