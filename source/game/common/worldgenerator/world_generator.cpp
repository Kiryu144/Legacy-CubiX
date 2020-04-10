/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_generator.h"

#include "game/common/world/world_chunk.h"

namespace Game
{

int WorldGenerator::getHeight( const glm::ivec2& worldPosition )
{
	return 0;
}

void WorldGenerator::setVoxel( Voxel& voxel, unsigned int blocksUnderground )
{
	if( blocksUnderground == 0 )
	{
		voxel = Voxel( { 88, 237, 110, 255 } );
	}
	else
	{
		voxel = Voxel( { 166, 166, 166, 255 } );
	}
}

Voxel WorldGenerator::getWaterVoxel()
{
	return { 51, 170, 255, 255 };
}

void WorldGenerator::generateHeight( WorldChunk& chunk )
{
	prepareForChunk( chunk.getChunkPosition() );
	glm::ivec3 worldPosition = chunk.getWorldPosition();
	bool generateChunkOnTop{ false };
	bool generateChunkOnBottom{ false };
	for( int x = 0; x < chunk.getSideLength(); ++x )
	{
		for( int z = 0; z < chunk.getSideLength(); ++z )
		{
			int y = getHeight( { chunk.getChunkPosition().x * chunk.getSideLength() + x,
								 chunk.getChunkPosition().z * chunk.getSideLength() + z } );

			if( y < worldPosition.y )
			{
				generateChunkOnBottom = true;

				if( worldPosition.y < 0 )
				{
					for( int _y = 0; _y > y && _y < WorldChunk::s_sideLength; ++_y )
					{
						chunk.set( { x, _y, z }, getWaterVoxel() );
					}
				}
				continue;
			}

			if( y >= ( worldPosition.y + static_cast< int >( chunk.getSideLength() ) ) )
			{
				generateChunkOnTop = true;
				continue;
			}

			unsigned int depth = 0;
			for( int _y = WorldChunk::s_sideLength - 1; _y >= 0; --_y )
			{
				if( _y <= y - worldPosition.y )
				{
					setVoxel( chunk.get( { x, _y, z } ), depth++ );
				}
				else if( worldPosition.y < 0 )
				{
					chunk.set( { x, _y, z }, getWaterVoxel() );
				}
			}
		}
	}

	if( generateChunkOnTop )
	{
		chunk.getWorld().generateChunk( chunk.getChunkPosition() + glm::ivec3{ 0, 1, 0 } );
	}
	if( generateChunkOnBottom )
	{
		chunk.getWorld().generateChunk( chunk.getChunkPosition() + glm::ivec3{ 0, -1, 0 } );
	}
}

void WorldGenerator::populate( WorldChunk& chunk )
{
	if( m_trees.empty() )
	{
		return;
	}

	srand( static_cast< unsigned int >( chunk.getPosition().x * 22222.55345
										+ chunk.getPosition().z * M_PI_4 * 200 * getSeed() ) );
	int trees = rand() % 16;
	for( int i = 0; i < trees; ++i )
	{
		auto& treeVoxelGroup = m_trees.at( rand() % m_trees.size() );
		glm::ivec2 randomPos{ rand() % WorldChunk::s_sideLength,
							  rand() % WorldChunk::s_sideLength };



	}
}

void WorldGenerator::addTree( std::shared_ptr< VoxelGroup >& tree )
{
	m_trees.push_back( { tree } );
}

} // namespace Game