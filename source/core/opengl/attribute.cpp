/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "attribute.h"

#include "core/cubix_assert.h"
#include "core/opengl/openg_error.h"
#include "core/opengl/opengl_helper.h"

namespace Core
{

SingleAttribute::SingleAttribute( GLenum dataType, size_t scalars, bool normalize )
	: m_dataType( dataType ), m_scalars( scalars ), m_normalize( normalize )
{
	cubix_assert( scalars >= 0 && scalars <= 4, "Scalar out of range." );
}

size_t SingleAttribute::getDataTypeSize() const
{
	switch( m_dataType )
	{
	case GL_BYTE:
		return sizeof( GLbyte );
	case GL_UNSIGNED_BYTE:
		return sizeof( GLubyte );
	case GL_SHORT:
		return sizeof( GLshort );
	case GL_UNSIGNED_SHORT:
		return sizeof( GLushort );
	case GL_INT:
		return sizeof( GLint );
	case GL_UNSIGNED_INT:
		return sizeof( GLuint );
	case GL_FLOAT:
		return sizeof( GLfloat );
	default:
		cubix_assert( false, "Not supported datatype " + to_string( m_dataType ) );
	}
	return 1;
}

size_t SingleAttribute::getTotalSize( size_t nVertices ) const
{
	return getDataTypeSize() * m_scalars * nVertices;
}

void SingleAttribute::bindVertexAttribPointer( size_t index )
{
	gl_log_error(
		glVertexAttribPointer( index, getScalars(), getDataType(), getNormalized(), 0, nullptr ) );
}

InterleavedAttribute::InterleavedAttribute(
	std::initializer_list< SingleAttribute > attributes)
	: m_attributes( attributes )
{
	cubix_assert( m_attributes.size() > 0, "No attributes provided" );
	for( auto& attribute : m_attributes )
	{
		m_stride += attribute.getDataTypeSize() * attribute.getScalars();
	}
}

void InterleavedAttribute::bindVertexAttribPointer( size_t index )
{
	size_t offset = 0;
	for( auto& attribute : m_attributes )
	{
		glEnableVertexAttribArray(index);
		gl_log_error( glVertexAttribPointer( index++,
											 attribute.getScalars(),
											 attribute.getDataType(),
											 attribute.getNormalized(),
											 m_stride,
											 ( void* )offset ) );
		offset += attribute.getDataTypeSize() * attribute.getScalars();
	}
}

size_t InterleavedAttribute::getTotalSize( size_t nVertices ) const
{
	return m_stride * nVertices;
}

} // namespace Core
