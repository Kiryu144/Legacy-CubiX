/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_RENDERABLE_H
#define CUBIX_RENDERABLE_H

#include "core/data/registry.h"
#include "core/opengl/attributebuffer.h"
#include "core/opengl/shader_program.h"

namespace Game
{

class Renderable
{
public:
public:
	virtual GLenum getDrawMode()
	{
		return GL_TRIANGLES;
	}
	virtual void setUniforms( Core::ShaderProgram& shader ) = 0;
	virtual Core::AttributeBuffer& getAttributeBuffer()		= 0;
	virtual Core::RegistryKey getShader()					= 0;
};

} // namespace Game

#endif // CUBIX_RENDERABLE_H
