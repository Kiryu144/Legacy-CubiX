/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_RENDERER_H
#define CUBIX_RENDERER_H

#include "core/event.h"
#include "core/io/window.h"
#include "core/opengl/shader_program.h"

#include "game/common/world/world.h"
#include "core/math/transform.h"

namespace Game
{

class Renderer
{
protected:
	Core::ShaderProgram m_chunkShader;
	glm::mat4 m_projection;
	glm::mat4 m_view;

public:
	void loadShaders();

	void setView( const glm::mat4& view );
	void render( World& world );
	void setProjection( const glm::mat4& projection );
};

} // namespace Game

#endif
