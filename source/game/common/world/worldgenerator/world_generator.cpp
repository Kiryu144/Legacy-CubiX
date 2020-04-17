/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_generator.h"

namespace Game
{

int WorldGenerator::getHeight( const glm::ivec2& worldPosition ) const
{
	return 0;
}

Voxel WorldGenerator::getVoxel( unsigned int blocksUnderground ) const
{
	if( blocksUnderground == 0 )
	{
		return { 88, 237, 110, 255 };
	}
	else
	{
		return { 166, 166, 166, 255 };
	}
}

Voxel WorldGenerator::getWaterVoxel() const
{
	return { 51, 170, 255, 255 };
}

void WorldGenerator::generateHeight( std::shared_ptr< IWorldChunk > chunk )
{
	prepareForChunk( chunk->getChunkPosition() );
	glm::ivec3 worldPosition = IWorldChunk::WorldPosFromChunkPos( chunk->getChunkPosition() );
	bool generateChunkOnTop{ false };
	bool generateChunkOnBottom{ false };
	for( int x = 0; x < IWorldChunk::GetSideLength(); ++x )
	{
		for( int z = 0; z < IWorldChunk::GetSideLength(); ++z )
		{
			int y = getHeight( { chunk->getChunkPosition().x * IWorldChunk::GetSideLength() + x,
								 chunk->getChunkPosition().z * IWorldChunk::GetSideLength() + z } );

			if( y < worldPosition.y )
			{
				generateChunkOnBottom = true;

				if( worldPosition.y < 0 )
				{
					for( int _y = 0; _y > y && _y < IWorldChunk::GetSideLength(); ++_y )
					{
						chunk->setVoxel( { x, _y, z }, getWaterVoxel() );
					}
				}
				continue;
			}

			if( y >= ( worldPosition.y + static_cast< int >( IWorldChunk::GetSideLength() ) ) )
			{
				generateChunkOnTop = true;
				continue;
			}

			unsigned int depth = 0;
			for( int _y = IWorldChunk::GetSideLength() - 1; _y >= 0; --_y )
			{
				if( _y <= y - worldPosition.y )
				{
					chunk->setVoxel( { x, _y, z }, getVoxel( depth ) );
				}
				else if( worldPosition.y < 0 )
				{
					chunk->setVoxel( { x, _y, z }, getWaterVoxel() );
				}
			}
		}
	}

	if( generateChunkOnTop )
	{
		chunk->getWorld().generateChunk( chunk->getChunkPosition() + glm::ivec3{ 0, 1, 0 } );
	}
	if( generateChunkOnBottom )
	{
		chunk->getWorld().generateChunk( chunk->getChunkPosition() + glm::ivec3{ 0, -1, 0 } );
	}
}

void WorldGenerator::populate( std::shared_ptr< IWorldChunk > chunk )
{
	if( m_trees.empty() )
	{
		return;
	}
}

void WorldGenerator::addTree( std::shared_ptr< VoxelGroup >& tree )
{
	m_trees.push_back( { tree } );
}

} // namespace Game