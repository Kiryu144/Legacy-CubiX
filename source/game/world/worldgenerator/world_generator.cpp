/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_generator.h"

#include "game/world/chunk/world_chunk.h"
#include "game/world/chunk/world_chunk_column.h"
#include "game/world/world.h"
#include "game/world/worldgenerator/biome/biome.h"
#include "game/world/worldgenerator/biome/flat.h"
#include "game/world/worldgenerator/biome/hilly_plains.h"

#include <set>

#include <glm/gtx/hash.hpp>

namespace Game
{

WorldGenerator::WorldGenerator( World& world ) : m_world( world )
{
	m_biome.reset( new Biome( 25, 10 ) );
	m_hillyPlains.reset( new HillyPlains() );
	m_flat.reset( new Flat() );

	m_baseHeight.SetSeed( 123 );
	m_moisture.SetSeed( m_baseHeight.GetSeed() + 28101999 );
	m_color.SetSeed( m_baseHeight.GetSeed() + -13141 );
}

void WorldGenerator::generateHeight( const std::shared_ptr< WorldChunkColumn >& column ) const
{
	glm::ivec3 chunkPosition{ column->getChunkPosition().x, 0, column->getChunkPosition().y };
	glm::ivec3 startWorldPosition{ WorldChunk::WorldPosFromChunkPos( chunkPosition ) };
	for( int x = 0; x < WorldChunk::GetSideLength(); ++x )
	{
		for( int z = 0; z < WorldChunk::GetSideLength(); ++z )
		{
			glm::ivec3 worldPos{ startWorldPosition + glm::ivec3{ x, 0, z } };

			float elevation{ m_baseHeight.GetPerlin( worldPos.x, worldPos.z ) };
			float moisture{ m_moisture.GetPerlin( worldPos.x, worldPos.z ) };
			float color{ m_color.GetPerlin( worldPos.x * 160, worldPos.z * 160 ) * 5 };
			auto biome{ getBiome( elevation, moisture ) };

			int voxelHeight{ biome->getBaseHeight()
							 + static_cast< int >( elevation * biome->getHeightVariation() ) };

			chunkPosition.y = WorldChunk::ChunkPosFromWorldPos( { 0, voxelHeight, 0 } ).y;
			auto chunk{ column->getOrCreateChunk( chunkPosition.y ) };
			if( !chunk->isInitialized() )
			{
				chunk->initializeData();
			}
			// optimize: Cache chunks for heights

			unsigned int depth{ 0 };
			for( int y = voxelHeight - chunkPosition.y * WorldChunk::GetSideLength(); y >= 0; --y )
			{
				Voxel voxel{ m_biome->getVoxelForDepth( depth++ ) };
				voxel.r += color;
				voxel.g += color;
				voxel.b += color;
				chunk->setVoxel( { x, y, z }, voxel );
			}
		}
	}
}

std::shared_ptr< Biome > WorldGenerator::getBiome( float elevation, float moisture ) const
{
	return m_flat;
	if( elevation >= 0.5f )
	{
		return m_hillyPlains;
	}

	return m_biome;
}

} // namespace Game