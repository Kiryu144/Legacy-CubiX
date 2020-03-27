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

#include <atomic>
#include <map>

namespace Game
{

class Entity;

class World : public ProxySided
{
protected:
	std::map< glm::ivec3, WorldChunk, Vec2Functor< int > > m_chunks;

	std::list< std::unique_ptr< Game::Entity > > m_entities;

public:
	World( Proxy proxy );

	void loadOrCreate( const glm::ivec3& position );
	void update( float deltaTime );
	void draw( Core::ShaderProgram& shader, const glm::mat4& view, const glm::mat4& projection );
};

} // namespace Game

#endif
