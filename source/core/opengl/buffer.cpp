#include "buffer.h"

#include <cassert>

#include <glad/glad.h>

namespace Cubix
{
namespace Core
{
namespace GL
{

thread_local BindableStateID Buffer::bindableStateId( glBindBuffer, glDeleteBuffers );

Buffer::~Buffer()
{
	clear();
}

void Buffer::set( const void* data, const size_t& size, const Type& type )
{
	assert( data != nullptr );
	assert( size > 0 );

	if( !containsData() )
	{
		glGenBuffers( 1, &m_bufferId );
	}

	bind();
	glBufferData( static_cast< GLuint >( type ), size, data, GL_STATIC_DRAW );
	m_size = size;
	m_type = type;
}

void Buffer::set( const void* data, const size_t& size )
{
	set( data, size, Type::ARRAY_BUFFER );
}

void Buffer::bind() const
{
	assert( containsData() );
	bindableStateId.bind( this );
}

void Buffer::clear()
{
	bindableStateId.del( this );
	m_bufferId = 0;
	m_size	   = 0;
}

bool Buffer::containsData() const
{
	return m_bufferId > 0;
}

size_t Buffer::size() const
{
	return m_size;
}

unsigned int Buffer::getStateID() const
{
	return m_bufferId;
}

unsigned int Buffer::getTypeID() const
{
	return static_cast< unsigned int >( m_type );
}

} // namespace GL
} // namespace Core
} // namespace Cubix
