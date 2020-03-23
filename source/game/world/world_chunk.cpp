/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk.h"

namespace Game
{

unsigned int WorldChunk::s_sideLength = 32;

WorldChunk::WorldChunk( const glm::uvec3& chunkPosition )
	: VoxelGroup( glm::uvec3{ s_sideLength, s_sideLength, s_sideLength } ),
	  m_chunkPosition( chunkPosition )
{
	getPosition()
		= { chunkPosition.x * m_size.x, chunkPosition.y * m_size.y, chunkPosition.z * m_size.z };
}

void WorldChunk::generateFlat( unsigned int floorThickness )
{
	cubix_assert( floorThickness <= m_size.y, "Floor thickness is bigger than the chunk heigth" );

	for( int x = 0; x < m_size.x; ++x )
	{
		for( int y = 0; y < floorThickness; ++y )
		{
			for( int z = 0; z < m_size.z; ++z )
			{
				Voxel voxel( 73, 201 + ( rand() % 20 ), 98 );
				set( { x, y, z }, voxel, false );
			}
		}
	}

	updateAllFaces();
	regenerateMesh();
}

} // namespace Game