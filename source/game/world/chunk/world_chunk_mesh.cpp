/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_mesh.h"

#include "game/world/chunk/world_chunk.h"
#include "game/world/chunk/world_chunk_layer.h"
#include "game/world/world.h"

#include <core/time/auto_stop_watch.h>

namespace Game
{

WorldChunkMesh::WorldChunkMesh( World& world, const glm::ivec2& chunkPos )
{
	for( int x = -1; x <= 1; ++x )
	{
		for( int z = -1; z <= 1; ++z )
		{
			m_chunks[ x + 1 ][ z + 1 ] = world.getChunk( chunkPos + glm::ivec2{ x, z } );
		}
	}
	cubix_assert( getChunk( { 0, 0 } ), "Invalid chunkpos provided" );
}

std::shared_ptr< WorldChunk > WorldChunkMesh::getChunk( const glm::ivec2& offset )
{
	return m_chunks[ offset.x + 1 ][ offset.y + 1 ];
}

const std::shared_ptr< WorldChunk > WorldChunkMesh::getChunk( const glm::ivec2& offset ) const
{
	return m_chunks[ offset.x + 1 ][ offset.y + 1 ];
}

Voxel WorldChunkMesh::getVoxel( const WorldPosition& position ) const
{
	auto chunkPos{ position.toChunkPosition() };
	auto& chunk{ getChunk( chunkPos ) };
	if( !chunk )
	{
		return Voxel();
	}
	return chunk->getVoxel( position.toInnerChunkOffset( chunkPos ) );
}

bool WorldChunkMesh::isRenderVoxel( const WorldPosition& position ) const
{
	auto voxel{ getVoxel( position ) };
	return voxel.exists() && voxel.a > 0;
}

void WorldChunkMesh::generate()
{
	m_vertices.clear();

	auto chunk{ getChunk( { 0, 0 } ) };
	VoxelCluster voxelCluster;
	for( int y = WorldChunk::GetMinYLevel(); y < WorldChunk::GetMaxYLevel(); ++y )
	{
		auto& layer{ chunk->getLayer( y ) };
		if( !layer )
		{
			continue;
		}

		for( int z = 0; z < CUBIX_CHUNK_SIZE; ++z )
		{
			for( int x = 0; x < CUBIX_CHUNK_SIZE; ++x )
			{
				WorldPosition worldPosition{ x, y, z };
				auto index{ WorldChunkLayer::GetIndexForLayer( { x, z } ) };
				auto voxel{ layer->getVoxel( index ) };
				auto exists{ voxel.exists() && voxel.a > 0 };

				if( !exists )
				{
					continue;
				}

				for( int _x = -1; _x <= 1; ++_x )
				{
					for( int _y = -1; _y <= 1; ++_y )
					{
						for( int _z = -1; _z <= 1; ++_z )
						{
							voxelCluster( _x, _y, _z )
								= isRenderVoxel( WorldPosition{ x + _x, y + _y, z + _z } );
						}
					}
				}

				pushFaces( worldPosition, voxelCluster, voxel );
			}
		}
	}
}

void WorldChunkMesh::pushFaces( const WorldPosition& pos,
								const WorldChunkMesh::VoxelCluster& cluster,
								const Core::Color& color )
{
	static const glm::vec3 positions[ 6 * 6 ]{
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

	static const glm::vec3 normals[ 6 ]{ glm::vec3( 0.0, 0.0, -1.0 ), glm::vec3( -1.0, 0.0, 0.0 ),
										 glm::vec3( 0.0, 0.0, 1.0 ),  glm::vec3( 1.0, 0.0, 0.0 ),
										 glm::vec3( 0.0, 1.0, 0.0 ),  glm::vec3( 0.0, -1.0, 0.0 ) };

	static const glm::ivec3 ambientOcclusion[ 6 * 6 * 3 ]{
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

	Core::MultipleFacing facings;
	facings.setFace( Core::MultipleFacing::LEFT, !cluster( 1, 0, 0 ) );
	facings.setFace( Core::MultipleFacing::BACK, !cluster( 0, 0, 1 ) );
	facings.setFace( Core::MultipleFacing::BOTTOM, !cluster( 0, 1, 0 ) );
	facings.setFace( Core::MultipleFacing::RIGHT, !cluster( -1, 0, 0 ) );
	facings.setFace( Core::MultipleFacing::FRONT, !cluster( 0, 0, -1 ) );
	facings.setFace( Core::MultipleFacing::TOP, !cluster( 0, -1, 0 ) );

	for( const auto& face : Core::MultipleFacing::Facings )
	{
		if( !facings.hasFace( face ) )
		{
			continue;
		}
		auto faceIndex{ Core::MultipleFacing::IndexOf( face ) };

		Vertex vertex;
		for( int vertice = 0; vertice < 6; ++vertice )
		{
			vertex.color	= color;
			vertex.position = glm::vec3( pos ) + positions[ faceIndex * 6 + vertice ];
			vertex.normal	= normals[ faceIndex ];

			int i{ faceIndex * 18 + vertice * 3 };
			bool s1{ cluster( ambientOcclusion[ i + 0 ] ) };
			bool s2{ cluster( ambientOcclusion[ i + 2 ] ) };
			bool c{ cluster( ambientOcclusion[ i + 1 ] ) };

			int acDarkness = ( s1 && s2 ) ? 3 : s1 + s2 + c;
			acDarkness *= 20;

			vertex.color.add( -acDarkness, -acDarkness, -acDarkness );
			m_vertices.push_back( vertex );
		}
	}
}

} // namespace Game