/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_generator.h"

#include "game/world/chunk/world_chunk.h"
#include "game/world/world.h"
#include "game/world/worldgenerator/biome/biome.h"
#include "game/world/worldgenerator/biome/flat.h"
#include "game/world/worldgenerator/biome/hilly_plains.h"

#include <set>

namespace Game
{

WorldGenerator::WorldGenerator( World& world ) : m_world( world )
{
	m_biome.reset( new Biome( 25, 10 ) );
	m_hillyPlains.reset( new HillyPlains() );
	m_flat.reset( new Flat() );

	m_baseHeight.SetSeed( 123 );
	m_moisture.SetSeed( m_baseHeight.GetSeed() + 28101999 );
}

void WorldGenerator::generateHeight( std::shared_ptr< WorldChunk >& chunk ) const
{
	for( int x = 0; x < CUBIX_CHUNK_SIZE; ++x )
	{
		for( int z = 0; z < CUBIX_CHUNK_SIZE; ++z )
		{
			auto worldPos = chunk->getChunkPosition().toWorldPosition( { x, 0, z } );

			float elevation{ m_baseHeight.GetPerlin( worldPos.x, worldPos.z ) };
			float moisture{ m_moisture.GetPerlin( worldPos.x, worldPos.z ) };
			auto biome{ getBiome( elevation, moisture ) };

			int voxelHeight{ biome->getBaseHeight()
							 + static_cast< int >( elevation * biome->getHeightVariation() ) };

			unsigned int depth{ 0 };
			for( int y = voxelHeight; y >= voxelHeight - biome->getHeightVariation(); --y )
			{
				chunk->setVoxel( { x, y, z }, m_biome->getVoxelForDepth( depth++ ) );
			}
		}
	}
}

std::shared_ptr< Biome > WorldGenerator::getBiome( float elevation, float moisture ) const
{
	return m_biome;
	if( elevation >= 0.5f )
	{
		return m_hillyPlains;
	}

	return m_biome;
}

} // namespace Game