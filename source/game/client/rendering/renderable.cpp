/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "renderable.h"

namespace Game
{

GLenum Game::Renderable::getDrawMode()
{
	return GL_TRIANGLES;
}

void Renderable::setUniforms( Core::ShaderProgram& shader ) {}

} // namespace Game