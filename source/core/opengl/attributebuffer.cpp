/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "attributebuffer.h"

Core::AttributeBuffer::AttributeBuffer( GLenum bufferTarget ) : m_bufferTarget( bufferTarget )
{
	glGenBuffers( 1, &m_id );
}

Core::AttributeBuffer::~AttributeBuffer()
{
	Core::Logger::Log( "Deleting " + std::to_string( m_size ) + "B from a "
					   + Core::to_string( m_bufferTarget ) + " buffer" );
	glDeleteBuffers( 1, &m_id );
	m_id = 0;
}

void Core::AttributeBuffer::bind( GLuint vertexAttribIndex )
{
	glBindVertexArray( m_id );
	glVertexAttribPointer( vertexAttribIndex,
						   m_sizePerSingle / sizeof( float ),
						   GL_FLOAT,
						   GL_FALSE,
						   m_sizePerSingle,
						   nullptr );
	glEnableVertexAttribArray( vertexAttribIndex );
}
