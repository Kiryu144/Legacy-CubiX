/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "attributebuffer.h"

#include "core/opengl/openg_error.h"

namespace Core
{

AttributeBuffer::AttributeBuffer( std::shared_ptr< Attribute > attribute, GLenum bufferTarget )
	: m_bufferTarget( bufferTarget ), m_attribute( attribute )
{
	cubix_assert( m_attribute.get() != nullptr, "Null attribute" );
}

void AttributeBuffer::bind( GLuint vertexAttribIndex )
{
	cubix_assert( m_totalSize > 0, "Unable to bind buffer with no data uploaded" );
	gl_clear_error();
	gl_log_error( glBindBuffer( m_bufferTarget, m_vbo.getID() ) );
	m_attribute->vertexAttribPointer( vertexAttribIndex );
}

void AttributeBuffer::upload( void* data, size_t vertices )
{
	cubix_assert( data != nullptr, "Nullptr data provided" );
	cubix_assert( vertices != 0, "Cannot upload data with zero vertices" );

	GLuint vbo{ 0 };
	glGenBuffers( 1, &vbo );
	m_vbo.reset( vbo );

	cubix_assert( vbo != 0, "Created VBO id is zero" );

	m_totalSize = static_cast< GLuint >( m_attribute->getSize( vertices ) );
	m_vertices	= static_cast< GLuint >( vertices );
	gl_log_error( glBindBuffer( m_bufferTarget, m_vbo.getID() ) );
	gl_log_error( glBufferData( m_bufferTarget, m_totalSize, data, GL_STATIC_DRAW ) );
}

bool AttributeBuffer::isValid() const
{
	return m_vbo.getID() > 0 && m_vertices > 0;
}

} // namespace Core
