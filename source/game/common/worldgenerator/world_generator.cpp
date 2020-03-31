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

void WorldGenerator::generateHeight( WorldChunk& chunk )
{
	prepareForChunk( chunk.getChunkPosition() );
	glm::ivec3 worldPosition = chunk.getWorldPosition();
	for( int x = 0; x < chunk.getSideLength(); ++x )
	{
		for( int z = 0; z < chunk.getSideLength(); ++z )
		{
			int y = getHeight( { chunk.getChunkPosition().x * chunk.getSideLength() + x,
								 chunk.getChunkPosition().z * chunk.getSideLength() + z } );
			if( y >= ( worldPosition.y + chunk.getSideLength() ) || y < worldPosition.y )
			{
				continue;
			}

			unsigned int depth = 0;
			for( int _y = y - worldPosition.y; _y >= 0; --_y )
			{
				setVoxel( chunk.get( { x, _y, z } ), depth++ );
			}
		}
	}
}

} // namespace Game