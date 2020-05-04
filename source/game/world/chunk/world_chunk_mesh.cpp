/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_mesh.h"

#include "game/world/chunk/world_chunk_layer.h"
#include "game/world/world.h"

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
}

std::shared_ptr< WorldChunk > WorldChunkMesh::getChunk( const glm::ivec2& offset )
{
	return m_chunks[ offset.x ][ offset.y ];
}

void WorldChunkMesh::generate()
{
	m_vertices.clear();

	auto& chunk{ getChunk( { 0, 0 } ) };
	VoxelCluster voxelCluster;
	std::memset( &voxelCluster, false, sizeof( VoxelCluster ) );
	for( int y = WorldChunk::GetMinYLevel(); y < WorldChunk::GetMaxYLevel(); ++y )
	{
		auto& layer{ chunk->getLayer( y ) };
		if( !layer )
		{
			continue;
		}

		for( int z = 0; z < WorldChunk::GetSideLength(); ++z )
		{
			for( int x = 0; x < WorldChunk::GetSideLength(); ++x )
			{
				auto index{ WorldChunkLayer::GetIndexForLayer( { x, z } ) };
				auto voxel{ layer->getVoxel( index ) };
				auto exists{ voxel.exists() && voxel.a > 0 };
				voxelCluster( x - 1, y, z ) = voxelCluster( x, y, z );
				voxelCluster(x, y, z) = exists;
			}

			voxelCluster( x, y, z ) = voxelCluster( x + 1, y, z );
		}
	}
}

} // namespace Game