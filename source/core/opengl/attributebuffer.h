/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_ATTRIBUTEBUFFER_H
#define CUBIX_ATTRIBUTEBUFFER_H

#include <glad/glad.h>

#include "core/opengl/openg_error.h"
#include "opengl_helper.h"

namespace Core
{

class AttributeBuffer
{
private:
	GLenum m_bufferTarget;
	GLuint m_id;
	size_t m_size;
	size_t m_sizePerSingle;

public:
	AttributeBuffer( GLenum bufferTarget );
	AttributeBuffer( const AttributeBuffer& other ) = delete;
	~AttributeBuffer();
	AttributeBuffer& operator=( AttributeBuffer& other ) = delete;

	template< typename T >
	void upload( T* data, size_t amount )
	{
		m_sizePerSingle = sizeof( T );
		m_size			= sizeof( T ) * amount;
		Core::Logger::Log( "Uploading " + std::to_string( m_size ) + "B data to a "
						   + Core::to_string( m_bufferTarget ) + " buffer" );
		gl_log_error( glBindBuffer( m_bufferTarget, m_id ) );
		gl_log_error( glBufferData( m_bufferTarget, m_size, data, GL_STATIC_DRAW ) );
	}

	void bind( GLuint vertexAttribIndex );
};

} // namespace Core

#endif
