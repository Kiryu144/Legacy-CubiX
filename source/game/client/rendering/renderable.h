/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_RENDERABLE_H
#define CUBIX_RENDERABLE_H

#include <glad/glad.h>

namespace Core
{
class ShaderProgram;
class AttributeBuffer;
class RegistryKey;
} // namespace Core

namespace Game
{

class Renderable
{
public:
public:
	virtual GLenum getDrawMode();
	virtual void setUniforms( Core::ShaderProgram& shader );
	virtual Core::AttributeBuffer& getAttributeBuffer() = 0;
	virtual Core::RegistryKey getShader()				= 0;
};

} // namespace Game

#endif // CUBIX_RENDERABLE_H
