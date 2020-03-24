/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_H
#define CUBIX_WORLD_H

#include "world_chunk.h"
#include "core/math/glm_math.h"
#include "core/opengl/shader_program.h"
#include "game/proxy.h"

#include <map>

namespace Game
{

class World : public ProxySided
{
protected:
	std::map< glm::ivec3, WorldChunk, Vec2Functor< int > > m_chunks;

	Core::ShaderProgram m_shaderProgram;

public:
	World( Proxy proxy );

	void loadOrCreate( const glm::ivec3& position );
	void draw( Core::ShaderProgram& shader, const glm::mat4& view, const glm::mat4& projection );
};

} // namespace Game

#endif
