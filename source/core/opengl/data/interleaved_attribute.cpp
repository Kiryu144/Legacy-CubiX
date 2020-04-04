/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "interleaved_attribute.h"

#include "core/cubix_assert.h"
#include "core/opengl/openg_error.h"

namespace Core
{

InterleavedAttribute::InterleavedAttribute(
	const std::initializer_list< SingleAttribute >& attributes )
	: m_attributes( attributes )
{
	cubix_assert( m_attributes.size() > 0, "Empty attribute list provided" );
	m_stride = 0;
	for( auto& attribute : m_attributes )
	{
		m_stride += attribute.getSize();
	}
}

void InterleavedAttribute::vertexAttribPointer( unsigned int index )
{
	size_t offset = 0;
	for( auto& attribute : m_attributes )
	{
		glEnableVertexAttribArray( index );
		gl_log_error( glVertexAttribPointer( index++,
											 attribute.getScalars(),
											 attribute.getType(),
											 static_cast< GLboolean >( attribute.getNormalize() ),
											 static_cast< GLsizei >( m_stride ),
											 ( void* )offset ) );
		offset += attribute.getSize( 1 );
	}
}

size_t InterleavedAttribute::getSize( unsigned int multiplier )
{
	return m_stride * multiplier;
}

} // namespace Core