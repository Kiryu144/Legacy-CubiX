/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_H
#define CUBIX_WORLD_H

#include "game/world/chunk/chunk_worker.h"
#include "game/world/chunk/world_chunk_container.h"
#include "game/world/worldgenerator/world_generator.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace Core
{
class AxisAlignedBB;
}

namespace Game
{

class Cubix;
class Renderer;
class Entity;
class PlacedVoxel;

class World : public WorldChunkContainer
{
public:
	typedef std::unordered_set< glm::ivec3 > ChunkQueue;

protected:
	Cubix& m_game;
	WorldGenerator m_worldGenerator;
	ChunkWorker m_chunkWorker;
	Renderer* m_renderer;

	std::list< std::shared_ptr< Entity > > m_entities;

public:
	World( Cubix& game, Renderer* renderer );
	virtual ~World() = default;
	virtual void update( float deltaTime );

	CUBIX_GET_R_CR( m_game, Game );
	CUBIX_GET_R_CR( m_worldGenerator, WorldGenerator );
	CUBIX_GET_R_CR( m_chunkWorker, ChunkWorker );
	CUBIX_GET_SET_R_CR( m_renderer, Renderer );

	void updateForPlayer( const glm::ivec2& chunkPosition );
	void summonEntity( std::shared_ptr< Entity > m_entity );

	std::optional< glm::ivec3 > raycastBlocks( const glm::vec3& start,
											   const glm::vec3& direction,
											   int maxDistance ) const;
	size_t calculateVoxelMemoryConsumption() const;
};

} // namespace Game

#endif
