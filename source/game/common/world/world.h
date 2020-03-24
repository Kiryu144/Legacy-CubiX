/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_H
#define CUBIX_WORLD_H

#include "world_chunk.h"
#include "core/math/glm_math.h"
#include "core/opengl/shader_program.h"

#include <map>

namespace Game
{

class World
{
protected:
	std::map< glm::ivec3, WorldChunk, Vec2Functor< int > > m_chunks;

	Core::ShaderProgram m_shaderProgram;

public:
	World();

	void loadOrCreate( const glm::ivec3& position );
	void draw( const glm::mat4& view, const glm::mat4& projection );
};

} // namespace Game

#endif
