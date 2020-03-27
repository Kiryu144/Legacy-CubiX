/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk.h"

#include "fast_noise/FastNoise.h"

namespace Game
{

unsigned int WorldChunk::s_sideLength = 32;

WorldChunk::WorldChunk( const glm::ivec3& chunkPosition )
	: VoxelGroup( glm::uvec3{ s_sideLength, s_sideLength, s_sideLength } ),
	  m_chunkPosition( chunkPosition )
{
	getPosition() = glm::ivec3{ chunkPosition.x * getSize().x,
								chunkPosition.y * getSize().y,
								chunkPosition.z * getSize().z };
}

void WorldChunk::generateFlat( unsigned int floorThickness )
{
	cubix_assert( floorThickness <= getSize().y,
				  "Floor thickness is bigger than the chunk heigth" );

	for( int x = 0; x < getSize().x; ++x )
	{
		for( int y = 0; y < floorThickness; ++y )
		{
			for( int z = 0; z < getSize().z; ++z )
			{
				Voxel voxel( 73, 201 + ( rand() % 20 ), 98 );
				set( { x, y, z }, voxel, false );
			}
		}
	}
}

void WorldChunk::generateBasicNoise()
{
	FastNoise noise;
	noise.SetNoiseType( FastNoise::NoiseType::PerlinFractal );

	for( int x = 0; x < getSize().x; ++x )
	{
		for( int z = 0; z < getSize().z; ++z )
		{
			Voxel voxel( 73, 201 + ( rand() % 20 ), 98 );
			glm::ivec2 worldPos{ m_chunkPosition.x * s_sideLength + x,
								 m_chunkPosition.z * s_sideLength + z };

			auto n = ( noise.GetNoise( worldPos.x, worldPos.y ) + 1 ) / 2.0f;

			for( int y = n * ( s_sideLength - 1 ); y >= 0; --y )
			{
				set( { x, y, z }, voxel, false );
			}
		}
	}
}

std::mutex& WorldChunk::getMutex()
{
	return m_mutex;
}

const std::mutex& WorldChunk::getMutex() const
{
	return m_mutex;
}

} // namespace Game