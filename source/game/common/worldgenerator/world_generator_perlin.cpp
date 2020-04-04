/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_generator_perlin.h"

namespace Game
{

int WorldGeneratorPerlin::getHeight( const glm::ivec2& worldPosition )
{
	auto n1 = noise.GetNoise( worldPosition.x / 4.0f, worldPosition.y / 4.0f ) * 60;
	auto n2 = noise.GetNoise( worldPosition.x / 0.5f, worldPosition.y / 0.5f ) * 5;

	return static_cast< int >( n1 + n2 );
}

void WorldGeneratorPerlin::prepareForChunk( const glm::ivec3& chunkPosition )
{
	noise = FastNoise( getSeed() );
	noise.SetNoiseType( FastNoise::PerlinFractal );
}

} // namespace Game