/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_GENERATOR_H
#define CUBIX_WORLD_GENERATOR_H

#include "core/cubix_macro.h"

#include <memory>

#include <fast_noise/FastNoise.h>

namespace Game
{

class World;
class WorldChunk;
class Biome;
class HillyPlains;
class Flat;

class WorldGenerator
{
protected:
	FastNoise m_baseHeight;
	FastNoise m_moisture;

	World& m_world;
	std::shared_ptr< Biome > m_biome;
	std::shared_ptr< HillyPlains > m_hillyPlains;
	std::shared_ptr< Flat > m_flat;

	std::shared_ptr< Biome > getBiome( float elevation, float moisture ) const;

public:
	WorldGenerator( World& world );

	CUBIX_GET_R_CR( m_world, World );

	void generateHeight( std::shared_ptr< WorldChunk >& chunk ) const;
};

} // namespace Game

#endif
