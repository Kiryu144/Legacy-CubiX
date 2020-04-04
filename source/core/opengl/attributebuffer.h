/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_ATTRIBUTEBUFFER_H
#define CUBIX_ATTRIBUTEBUFFER_H

#include "core/cubix_assert.h"
#include "core/cubix_macro.h"
#include "core/logic/no_copy.h"
#include "core/opengl/data/attribute.h"
#include "core/opengl/opengl_helper.h"

#include <glad/glad.h>

namespace Core
{

class AttributeBuffer : public NoCopy
{
private:
	DestructibleGLuint< BufferDeleter > m_vbo;
	std::shared_ptr< Attribute > m_attribute;

	GLenum m_bufferTarget{ 0 };
	GLuint m_vertices{ 0 };
	GLuint m_totalSize{ 0 };

public:
	AttributeBuffer( std::shared_ptr< Attribute > attribute,
					 GLenum bufferTarget = GL_ARRAY_BUFFER );

	void upload( void* data, size_t vertices );
	void bind( GLuint vertexAttribIndex );

	CUBIX_GET_V( m_vertices, VerticeAmount );
	CUBIX_GET_V( m_totalSize, TotalSize );
};

} // namespace Core

#endif
