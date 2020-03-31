/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_generator_perlin.h"

namespace Game
{

int WorldGeneratorPerlin::getHeight( const glm::ivec2& worldPosition )
{
	return static_cast< int >( noise.GetNoise( worldPosition.x / 2.0f, worldPosition.y / 2.0f )
							   * 50 );
}

void WorldGeneratorPerlin::prepareForChunk( const glm::ivec3& chunkPosition )
{
	noise = FastNoise( getSeed() );
	noise.SetNoiseType( FastNoise::PerlinFractal );
}

} // namespace Game