/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_GENERATOR_PERLIN_H
#define CUBIX_WORLD_GENERATOR_PERLIN_H

#include "world_generator.h"

#include <fast_noise/FastNoise.h>

namespace Game
{

class WorldGeneratorPerlin : public WorldGenerator
{
private:
	FastNoise noise;

protected:
	void prepareForChunk( const glm::ivec3& chunkPosition ) override;
	int getHeight( const glm::ivec2& worldPosition ) const override;
};

} // namespace Game

#endif
