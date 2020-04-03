/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "attributebuffer.h"

Core::AttributeBuffer::AttributeBuffer( GLenum bufferTarget,
										std::shared_ptr< Attribute > attribute )
	: m_bufferTarget( bufferTarget ), m_attribute( attribute )
{
	cubix_assert( m_attribute.get() != nullptr, "Null attribute" );
}

Core::AttributeBuffer::~AttributeBuffer()
{
	if( m_id > 0 )
	{
		glDeleteBuffers( 1, &m_id );
		m_id = 0;
	}
}

void Core::AttributeBuffer::bind( GLuint vertexAttribIndex )
{
	cubix_assert( m_totalSize > 0, "Unable to bind buffer with no data uploaded" );
	glBindBuffer( m_bufferTarget, m_id );
	m_attribute->bindVertexAttribPointer( vertexAttribIndex );
	glEnableVertexAttribArray( vertexAttribIndex );
}

GLuint Core::AttributeBuffer::getVerticeAmount() const
{
	return m_vertices;
}
