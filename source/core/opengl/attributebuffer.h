/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_ATTRIBUTEBUFFER_H
#define CUBIX_ATTRIBUTEBUFFER_H

#include <glad/glad.h>

#include "core/opengl/openg_error.h"
#include "core/opengl/opengl_helper.h"
#include "core/cubix_assert.h"
#include "core/opengl/attribute.h"

namespace Core
{

class AttributeBuffer
{
private:
	GLenum m_bufferTarget{ 0 };
	GLuint m_id{ 0 };
	GLuint m_vertices{ 0 };
	GLuint m_totalSize{ 0 };
	Attribute m_attribute;

public:
	AttributeBuffer( GLenum bufferTarget, Attribute attribute );
	AttributeBuffer( const AttributeBuffer& other ) = delete;
	~AttributeBuffer();
	AttributeBuffer& operator=( AttributeBuffer& other ) = delete;

	template< typename T >
	void upload( T* data, size_t amount )
	{
		cubix_assert( sizeof( T ) == m_attribute.getTotalSize( 1 ), "Invalid datatype provided" );
		m_vertices	= amount;
		m_totalSize = m_attribute.getTotalSize( m_vertices );
		Core::Logger::Log( "Uploading " + std::to_string( m_totalSize ) + "B data to a "
						   + Core::to_string( m_bufferTarget ) + " buffer" );
		gl_log_error( glBindBuffer( m_bufferTarget, m_id ) );
		gl_log_error( glBufferData( m_bufferTarget, m_totalSize, data, GL_STATIC_DRAW ) );
	}

	void bind( GLuint vertexAttribIndex );
};

} // namespace Core

#endif
