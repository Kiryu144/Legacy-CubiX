/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_H
#define CUBIX_WORLD_H

#include "world_chunk.h"

#include "core/math/glm_math.h"
#include "core/opengl/shader_program.h"

#include "game/common/entity/entity.h"
#include "game/proxy.h"

#include <set>
#include <unordered_map>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace Game
{

class Entity;

class World : public ProxySided
{
protected:
	std::unordered_map< glm::ivec3, std::shared_ptr< WorldChunk > > m_chunks;
	std::list< std::unique_ptr< Game::Entity > > m_entities;

public:
	World( const Proxy& proxy );
	virtual ~World() = default;
	virtual void update( float deltaTime );
};

} // namespace Game

#endif
