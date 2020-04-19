/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "single_attribute.h"

#include "core/cubix_assert.h"
#include "core/opengl/opengl_helper.h"

namespace Core
{

SingleAttribute::SingleAttribute( GLenum type, unsigned int scalars, bool normalize )
	: m_type( type ),
	  m_scalars( scalars ),
	  m_normalize( normalize ),
	  m_size( GetSizeOfGLType( m_type ) * m_scalars )
{
	cubix_assert( scalars >= 1 && scalars <= 4, "Scalars out of range" );
}

void SingleAttribute::vertexAttribPointer( unsigned int index )
{
	glEnableVertexAttribArray( index );
	glVertexAttribPointer(
		index, getScalars(), getType(), static_cast< GLboolean >( getNormalize() ), 0, nullptr );
}

size_t SingleAttribute::getSize( unsigned int multiplier )
{
	return m_size * multiplier;
}

} // namespace Core