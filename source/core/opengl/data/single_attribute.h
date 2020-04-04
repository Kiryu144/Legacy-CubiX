/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_SINGLE_ATTRIBUTE_H
#define CUBIX_SINGLE_ATTRIBUTE_H

#include "core/cubix_macro.h"
#include "core/opengl/data/attribute.h"

#include <memory>

#include <glad/glad.h>

namespace Core
{

class SingleAttribute : public Attribute
{
protected:
	GLenum m_type;
	unsigned int m_scalars;
	bool m_normalize;
	size_t m_size;

public:
	SingleAttribute( GLenum type, unsigned int scalars, bool normalize = false );

	CUBIX_GET_CR( m_type, Type );
	CUBIX_GET_CR( m_scalars, Scalars );
	CUBIX_GET_CR( m_normalize, Normalize );

	void vertexAttribPointer( unsigned int index ) override;
	size_t getSize( unsigned int multiplier = 1 ) override;
};

static const std::shared_ptr< SingleAttribute > SingleVertexAttribute(
	new SingleAttribute( GL_FLOAT, 3, false ) );
static const std::shared_ptr< SingleAttribute > SingleNormalAttribute(
	new SingleAttribute( GL_FLOAT, 3, false ) );
static const std::shared_ptr< SingleAttribute > SingleColorByteAttribute(
	new SingleAttribute( GL_UNSIGNED_BYTE, 4, true ) );
static const std::shared_ptr< SingleAttribute > SingleColorFloatAttribute(
	new SingleAttribute( GL_FLOAT, 4, false ) );

} // namespace Core

#endif
