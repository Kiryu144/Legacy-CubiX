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
	Core::Logger::Log( "Deleting " + std::to_string( m_attribute.getTotalSize( m_vertices ) )
					   + "B from a " + Core::to_string( m_bufferTarget ) + " buffer" );
	glDeleteBuffers( 1, &m_id );
	m_id = 0;
}

void Core::AttributeBuffer::bind( GLuint vertexAttribIndex )
{
	cubix_assert( m_totalSize > 0, "Unable to bind buffer with no data uploaded" );
	glVertexAttribPointer( vertexAttribIndex,
						   m_attribute.getScalars(),
						   m_attribute.getDataType(),
						   GL_FALSE,
						   0,
						   nullptr );
	glEnableVertexAttribArray( vertexAttribIndex );
}
