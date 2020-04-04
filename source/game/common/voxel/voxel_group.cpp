/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "voxel_group.h"

#include "core/io/riff_parser.h"
#include "core/opengl/data/interleaved_attribute.h"

#include <cmath>

namespace Game
{

VoxelGroup::VoxelGroup( const glm::uvec3& size )
	: Core::Container3D< Voxel >( size ), m_vertices( Core::InterleavedVertNormColAttribute )
{
}

VoxelGroup::VoxelGroup( const std::string& voxFilePath )
	: Core::Container3D< Voxel >( { 1, 1, 1 } ), m_vertices( Core::InterleavedVertNormColAttribute )
{
	Core::RiffParser vox( voxFilePath );

	Core::RiffParser::Byte* size = vox.getMain().children.at( "SIZE" ).data;
	Core::RiffParser::Byte* xyzi = vox.getMain().children.at( "XYZI" ).data;

	// Read SIZE
	glm::uvec3 dimensions;
	dimensions.x = ( *reinterpret_cast< uint32_t* >( size + 0 ) );
	dimensions.z = ( *reinterpret_cast< uint32_t* >( size + 4 ) );
	dimensions.y = ( *reinterpret_cast< uint32_t* >( size + 8 ) );

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
		voxel.setFlag(Voxel::EXISTS, true);
		set( pos, voxel );
	}
}

void VoxelGroup::set( const glm::uvec3& pos, const Voxel& voxel )
{
	operator[]( pos ) = voxel;
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
					( pos.x >= getSize().x - 1 || get( pos + glm::uvec3{ 1, 0, 0 } ).a < 255 ) );
	facing.setFace( Facing::BACK,
					( pos.z >= getSize().z - 1 || get( pos + glm::uvec3{ 0, 0, 1 } ).a < 255 ) );
	facing.setFace( Facing::BOTTOM,
					( pos.y >= getSize().y - 1 || get( pos + glm::uvec3{ 0, 1, 0 } ).a < 255 ) );
	facing.setFace( Facing::RIGHT, ( pos.x <= 0 || get( pos + glm::uvec3{ -1, 0, 0 } ).a < 255 ) );
	facing.setFace( Facing::FRONT, ( pos.z <= 0 || get( pos + glm::uvec3{ 0, 0, -1 } ).a < 255 ) );
	facing.setFace( Facing::TOP, ( pos.y <= 0 || get( pos + glm::uvec3{ 0, -1, 0 } ).a < 255 ) );
	return facing;
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

	Core::Container3D< Core::Facing > faces( m_size );

	for( int x = 0; x < getSize().x; ++x )
	{
		for( int y = 0; y < getSize().y; ++y )
		{
			for( int z = 0; z < getSize().z; ++z )
			{
				faces[ { x, y, z } ] = findVisibleFaces( { x, y, z } );
			}
		}
	}

	m_verticeBuffer.clear();
	m_verticeBuffer.reserve( getSize().x * getSize().y * getSize().z * 6 );

	glm::vec3 halfSize{ getSize().x * 0.5f, getSize().y * 0.5f, getSize().z * 0.5f };

	m_voxelCount = 0;
	for( int x = 0; x < getSize().x; ++x )
	{
		for( int y = 0; y < getSize().y; ++y )
		{
			for( int z = 0; z < getSize().z; ++z )
			{
				const Voxel& voxel = operator[]( { x, y, z } );
				if( voxel.a == 0 || !voxel.exists() )
				{
					continue;
				}
				++m_voxelCount;

				const Core::Facing& visible = faces[ { x, y, z } ];
				// MultipleFacingData<uint8_t> light = voxel.getLightLevel();
				for( int i = 0; i < 6; ++i )
				{
					if( visible.hasFace( static_cast< Core::Facing::Face >( pow( 2.0, i ) ) ) )
					{
						Vertice vertice;
						vertice.m_color = voxel;
						// float lightMul = light.getFace(i) / 255.0f;
						for( int j = 0; j < 6; ++j )
						{
							vertice.m_position = s_vertices[ i * 6 + j ]
								+ glm::vec3( x, y , z );
							vertice.m_normal = s_normals[ i ];
							m_verticeBuffer.push_back( vertice );
						}
					}
				}
			}
		}
	}
	m_upload = true;
}

void VoxelGroup::upload()
{
	if( !m_upload || m_verticeBuffer.empty() )
	{
		return;
	}

	m_vertices.upload( &m_verticeBuffer[ 0 ], m_verticeBuffer.size() );
	m_upload = false;
}

Core::AttributeBuffer& VoxelGroup::getVertices()
{
	return m_vertices;
}

void VoxelGroup::serialize( std::ostream& out ) const
{
	Container3D::serialize( out );
}

void VoxelGroup::deserialize( std::istream& in )
{
	Container3D::deserialize( in );
}

void VoxelGroup::insert( const VoxelGroup& other, const glm::ivec3& position )
{
	glm::ivec3 min;
	glm::ivec3 max;
	glm::ivec3 diff;
	for( unsigned int i = 0; i < 3; ++i )
	{
		min[ i ] = std::min( static_cast<int>( m_size[ i ]), std::max( 0, position[ i ] ) );
		max[ i ] = std::min( static_cast<int>( m_size[ i ]), std::max( 0, position[ i ]  + static_cast<int>( other.m_size[ i ] )) );
		diff[ i ] = position[i] - min[i];
	}

	for( int x = min.x; x < max.x; ++x )
	{
		for( int y = min.y; y < max.y; ++y )
		{
			for( int z = min.z; z < max.z; ++z )
			{
				auto& voxel = other.get( glm::ivec3{ x, y, z } - min - diff );
				if( voxel.exists() )
				{
					set( { x, y, z }, voxel );
				}
			}
		}
	}
}

} // namespace Game
