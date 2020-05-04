/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_H
#define CUBIX_WORLD_H

#include "game/world/chunk/world_chunk_container.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace Core
{
class AxisAlignedBB;
}

namespace Game
{

class Renderer;
class Entity;
class PlacedVoxel;

class World : public WorldChunkContainer
{
public:
	typedef std::unordered_set< glm::ivec3 > ChunkQueue;

protected:
	Renderer* m_renderer;

	std::list< std::shared_ptr< Entity > > m_entities;

public:
	World( Renderer* renderer );
	virtual ~World() = default;
	virtual void tick();

	CUBIX_GET_SET_R_CR( m_renderer, Renderer );

	void summonEntity( std::shared_ptr< Entity > m_entity );

	std::optional< glm::ivec3 > raycastBlocks( const glm::vec3& start,
											   const glm::vec3& direction,
											   int maxDistance ) const;
};

} // namespace Game

#endif
