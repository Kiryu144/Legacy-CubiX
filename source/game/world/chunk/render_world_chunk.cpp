/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "render_world_chunk.h"

#include "core/opengl/data/interleaved_attribute.h"
#include "core/opengl/shader_program.h"

#include "game/rendering/renderer.h"
#include "game/world/world.h"

#include <string>

namespace Game
{

RenderWorldChunk::RenderWorldChunk( World& world, const glm::ivec3& chunkPosition )
	: WorldChunk( world, chunkPosition ), m_attributeBuffer( Core::InterleavedVertNormColAttribute )
{
	m_position			 = IWorldChunk::WorldPosFromChunkPos( chunkPosition );
	auto& shaderRegistry = world.getRenderer()->getShaderRegistry();
	m_shaderKey			 = shaderRegistry.getKey( "world_chunk_shader" ).value();
}

bool RenderWorldChunk::IsFullRenderVoxel( const glm::ivec3& pos,
										  const RenderWorldChunk::FullRenderVoxelBitset& bitset )
{
	return bitset[ IWorldChunk::GetIndexForPosition( pos ) ];
}

bool RenderWorldChunk::IsFullRenderVoxelSurr( const glm::ivec3& pos,
											  const FullRenderVoxelBitset ( *bitset )[ 3 ][ 3 ] )
{
	glm::ivec3 chunkOffset{
		std::floor( static_cast< float >( pos.x ) / IWorldChunk::GetSideLength() ),
		std::floor( static_cast< float >( pos.y ) / IWorldChunk::GetSideLength() ),
		std::floor( static_cast< float >( pos.z ) / IWorldChunk::GetSideLength() )
	};
	return IsFullRenderVoxel(
		pos - ( chunkOffset * glm::ivec3( IWorldChunk::GetSize() ) ),
		bitset[ chunkOffset.x + 1 ][ chunkOffset.y + 1 ][ chunkOffset.z + 1 ] );
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

int RenderWorldChunk::getACColorCorrectionForCube(
	const Core::MultipleFacing::Face& face,
	const glm::ivec3& pos,
	int index,
	const FullRenderVoxelBitset ( *bitset )[ 3 ][ 3 ] )
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
	int i{ Core::MultipleFacing::IndexOf( face ) * 18 + index * 3 };
	bool side1	= IsFullRenderVoxelSurr( pos + s_acLookups[ i + 0 ], bitset );
	bool corner = IsFullRenderVoxelSurr( pos + s_acLookups[ i + 1 ], bitset );
	bool side2	= IsFullRenderVoxelSurr( pos + s_acLookups[ i + 2 ], bitset );
	return ( side1 && side2 ) ? 3 : side1 + side2 + corner;
}

void RenderWorldChunk::regenerateMesh()
{
	{
		std::lock_guard< decltype( m_uploadMutex ) > lock_guard( m_uploadMutex );
		m_upload = false;
	}

	FullRenderVoxelBitset fullRenderBlocks[ 3 ][ 3 ][ 3 ];

	for( int x = -1; x <= 1; ++x )
	{
		for( int y = -1; y <= 1; ++y )
		{
			for( int z = -1; z <= 1; ++z )
			{
				auto chunk = m_world.getChunk( m_chunkPosition + glm::ivec3{ x, y, z } );
				if( chunk != nullptr )
				{
					fullRenderBlocks[ x + 1 ][ y + 1 ][ z + 1 ]
						= static_cast< decltype( this ) >( chunk.get() )->m_renderableVoxels;
				}
			}
		}
	}

	m_vertices.clear();
	m_vertices.reserve( GetVolume() );
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

				const auto& visibleFaces{ findVisibleFaces( pos, fullRenderBlocks ) };
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
						int acDarkness
							= getACColorCorrectionForCube( face, pos, vertice, fullRenderBlocks )
							* 20;
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

Core::MultipleFacing RenderWorldChunk::findVisibleFaces(
	const glm::uvec3& pos, const FullRenderVoxelBitset ( *bitset )[ 3 ][ 3 ] ) const
{
	using namespace Core;
	glm::ivec3 ipos{ pos };
	MultipleFacing facing;
	facing.setFace( MultipleFacing::LEFT,
					!IsFullRenderVoxelSurr( ipos + glm::ivec3{ 1, 0, 0 }, bitset ) );
	facing.setFace( MultipleFacing::BACK,
					!IsFullRenderVoxelSurr( ipos + glm::ivec3{ 0, 0, 1 }, bitset ) );
	facing.setFace( MultipleFacing::BOTTOM,
					!IsFullRenderVoxelSurr( ipos + glm::ivec3{ 0, 1, 0 }, bitset ) );
	facing.setFace( MultipleFacing::RIGHT,
					!IsFullRenderVoxelSurr( ipos + glm::ivec3{ -1, 0, 0 }, bitset ) );
	facing.setFace( MultipleFacing::FRONT,
					!IsFullRenderVoxelSurr( ipos + glm::ivec3{ 0, 0, -1 }, bitset ) );
	facing.setFace( MultipleFacing::TOP,
					!IsFullRenderVoxelSurr( ipos + glm::ivec3{ 0, -1, 0 }, bitset ) );
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

void RenderWorldChunk::setVoxel( const glm::uvec3& position, const Voxel& voxel )
{
	auto index			= GetIndexForPosition( position );
	auto& existingVoxel = m_data[ index ];

	if( existingVoxel.exists() != voxel.exists() )
	{
		m_voxelCount += voxel.exists() ? +1 : -1;
	}
	m_renderableVoxels[ index ] = voxel.exists();

	existingVoxel = voxel;
}

void RenderWorldChunk::setUniforms( Core::ShaderProgram& shader )
{
	shader.setUniform( shader.getTransformUniform(), getMatrix() );
}

Core::RegistryKey RenderWorldChunk::getShader()
{
	return m_shaderKey;
}

Core::AttributeBuffer& RenderWorldChunk::getAttributeBuffer()
{
	return m_attributeBuffer;
}

} // namespace Game