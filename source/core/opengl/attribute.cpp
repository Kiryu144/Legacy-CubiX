/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "attribute.h"

#include "core/cubix_assert.h"
#include "core/opengl/opengl_helper.h"

namespace Core
{

Attribute::Attribute( GLenum dataType, unsigned char scalars )
	: m_dataType( dataType ), m_scalars( scalars )
{
	cubix_assert( scalars >= 0 && scalars <= 4, "Scalar out of range." );
}

size_t Attribute::getDataTypeSize() const
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

const unsigned char Attribute::getScalars() const
{
	return m_scalars;
}

size_t Attribute::getTotalSize( size_t nVertices ) const
{
	return getDataTypeSize() * m_scalars * nVertices;
}
const GLenum Attribute::getDataType() const
{
	return m_dataType;
}

} // namespace Core