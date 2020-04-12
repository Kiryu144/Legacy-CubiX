/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk.h"

#include <glm/glm.hpp>

namespace Game
{

unsigned int WorldChunk::s_sideLength = 32;

WorldChunk::WorldChunk( World& world, const glm::ivec3& chunkPosition )
	: VoxelGroup( glm::uvec3{ s_sideLength, s_sideLength, s_sideLength } ),
	  m_chunkPosition( chunkPosition ),
	  m_world( world ),
	  m_millisecondsNotSeen( 0 ),
	  m_attributeBuffer( Core::InterleavedVertNormColAttribute )
{
	getPosition() = glm::ivec3{ chunkPosition.x * getSize().x,
								chunkPosition.y * getSize().y,
								chunkPosition.z * getSize().z };
}

void WorldChunk::serialize( std::ostream& out ) const
{
	VoxelGroup::serialize( out );
	out.write( reinterpret_cast< const char* >( &m_chunkPosition ),
			   sizeof( decltype( m_chunkPosition ) ) );
}

void WorldChunk::deserialize( std::istream& in )
{
	VoxelGroup::deserialize( in );
	in.read( reinterpret_cast< char* >( &m_chunkPosition ), sizeof( decltype( m_chunkPosition ) ) );
}

const glm::vec3& WorldChunk::GetPosForCube( const Core::Facing::Face& face, int index )
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
	return s_vertices[ static_cast< const int& >( face ) * 6 + index ];
}

const glm::vec3& WorldChunk::GetNormForCube( const Core::Facing::Face& face )
{
	static const glm::vec3 s_normals[ 6 ]{
		glm::vec3( 0.0, 0.0, -1.0 ), glm::vec3( -1.0, 0.0, 0.0 ), glm::vec3( 0.0, 0.0, 1.0 ),
		glm::vec3( 1.0, 0.0, 0.0 ),	 glm::vec3( 0.0, 1.0, 0.0 ),  glm::vec3( 0.0, -1.0, 0.0 )
	};
	return s_normals[ static_cast< const int& >( face ) ];
}

int WorldChunk::getACColorCorrectionForCube( const Core::Facing::Face& face,
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
	const int& i{ static_cast< const int& >( static_cast< const int& >( face ) * 18 + index * 3 ) };
	bool side1	= getSafe( pos + s_acLookups[ i + 0 ] ).exists();
	bool corner = getSafe( pos + s_acLookups[ i + 1 ] ).exists();
	bool side2	= getSafe( pos + s_acLookups[ i + 2 ] ).exists();
	return ( side1 && side2 ) ? 3 : side1 + side2 + corner;
}

void WorldChunk::generateMesh()
{
	m_uploadVertices = false;
	m_vertexBuffer.clear();
	m_vertexBuffer.reserve( getSize().x * getSize().y * getSize().z * 36 );
	for( int x = 0; x < getSize().x; ++x )
	{
		for( int y = 0; y < getSize().y; ++y )
		{
			for( int z = 0; z < getSize().z; ++z )
			{
				const glm::vec3 pos{ x, y, z };
				const Voxel voxel{ operator[]( pos ) };
				if( voxel.a == 0 )
				{
					continue;
				}

				const auto& visibleFaces{ findVisibleFaces( pos ) };
				for( const auto& face : Core::Facing::Facings )
				{
					if( !visibleFaces.hasFace( face ) )
					{
						continue;
					}
					const auto& faceID{ static_cast< const int& >( face ) };
					Vertex vertex;
					for( int vertice = 0; vertice < 6; ++vertice )
					{
						vertex.color	= voxel;
						vertex.position = pos + GetPosForCube( face, vertice );
						vertex.normal	= GetNormForCube( face );
						int acDarkness	= getACColorCorrectionForCube( face, pos, vertice );
						vertex.color.add( -acDarkness, -acDarkness, -acDarkness );
						m_vertexBuffer.push_back( vertex );
					}
				}
			}
		}
	}
	m_uploadVertices = true;
}

void WorldChunk::render( const View& view, const Projection& projection )
{
	if( !m_attributeBuffer.isValid() )
	{
		return;
	}
}

void WorldChunk::uploadMesh()
{
	if( m_uploadVertices )
	{
		m_uploadVertices = false;
		m_attributeBuffer.upload( &m_vertexBuffer.at( 0 ), m_vertexBuffer.size() );
		m_vertexBuffer.clear();
	}
}

unsigned int WorldChunk::getSideLength()
{
	return s_sideLength;
}

const glm::ivec3 WorldChunk::getWorldPosition() const
{
	return { m_chunkPosition.x * s_sideLength,
			 m_chunkPosition.y * s_sideLength,
			 m_chunkPosition.z * s_sideLength };
}

World& WorldChunk::getWorld() const
{
	return m_world;
}

} // namespace Game