/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_H
#define CUBIX_WORLD_H

#include "world_chunk.h"
#include "core/opengl/shader_program.h"

#include <map>

namespace Game
{

class World
{
protected:
	struct ChunksKeyFunc
	{
		bool operator()( const glm::uvec3& v1, const glm::uvec3& v2 ) const
		{
			return v1.x < v2.x
				|| ( v1.x == v2.x && ( v1.y < v2.y || ( v1.y == v2.y && v1.z < v2.z ) ) );
		}
	};

	std::map< glm::uvec3, WorldChunk, ChunksKeyFunc > m_chunks;

	Core::ShaderProgram m_shaderProgram;

public:
	World();

	void loadOrCreate( const glm::uvec3& position );
	void draw( const glm::mat4& view, const glm::mat4& projection );
};

} // namespace Game

#endif
