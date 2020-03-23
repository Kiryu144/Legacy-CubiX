/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "attributebuffer.h"

Core::AttributeBuffer::AttributeBuffer( GLenum bufferTarget, Attribute attribute )
	: m_bufferTarget( bufferTarget ), m_attribute( attribute )
{
	glGenBuffers( 1, &m_id );
}

Core::AttributeBuffer::~AttributeBuffer()
{
	glDeleteBuffers( 1, &m_id );
	m_id = 0;
}

void Core::AttributeBuffer::bind( GLuint vertexAttribIndex )
{
	cubix_assert( m_totalSize > 0, "Unable to bind buffer with no data uploaded" );
	glBindBuffer( m_bufferTarget, m_id );
	gl_log_error( glVertexAttribPointer( vertexAttribIndex,
										 m_attribute.getScalars(),
										 m_attribute.getDataType(),
										 m_attribute.getNormalize(),
										 0,
										 nullptr ) );
	glEnableVertexAttribArray( vertexAttribIndex );
}

GLuint Core::AttributeBuffer::getVerticeAmount() const
{
	return m_vertices;
}
