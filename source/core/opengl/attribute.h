/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_ATTRIBUTE_H
#define CUBIX_ATTRIBUTE_H

#include "core/cubix_macro.h"

#include <memory>
#include <vector>

#include <glad/glad.h>

namespace Core
{

class Attribute
{
public:
	virtual void bindVertexAttribPointer( size_t index )	  = 0;
	virtual size_t getTotalSize( size_t nVertices = 1 ) const = 0;
};

class SingleAttribute : public Attribute
{
protected:
	GLenum m_dataType; // GL_FLOAT, GL_INT, etc ..
	size_t m_scalars;  // 1 - 4
	bool m_normalize;

public:
	SingleAttribute( GLenum dataType, size_t scalars, bool normalize );

	size_t getDataTypeSize() const;
	size_t getTotalSize( size_t nVertices = 1 ) const override;

	CUBIX_GET_CR( m_dataType, DataType );
	CUBIX_GET_CR( m_scalars, Scalars );
	CUBIX_GET_CR( m_normalize, Normalized );

	void bindVertexAttribPointer( size_t index ) override;
};

class InterleavedAttribute : public Attribute
{
protected:
	std::vector< SingleAttribute > m_attributes;
	size_t m_stride{ 0 };

public:
	InterleavedAttribute( std::initializer_list< SingleAttribute > attributes );

	void bindVertexAttribPointer( size_t index ) override;
	size_t getTotalSize( size_t nVertices = 1 ) const override;
};

static const std::shared_ptr< SingleAttribute > SingleVertexAttribute(
	new SingleAttribute( GL_FLOAT, 3, false ) );
static const std::shared_ptr< SingleAttribute > SingleNormalAttribute(
	new SingleAttribute( GL_FLOAT, 3, false ) );
static const std::shared_ptr< SingleAttribute > SingleColorByteAttribute(
	new SingleAttribute( GL_UNSIGNED_BYTE, 4, true ) );
static const std::shared_ptr< SingleAttribute > SingleColorFloatAttribute(
	new SingleAttribute( GL_FLOAT, 4, false ) );

static const std::shared_ptr< InterleavedAttribute > InterleavedVertNormColAttribute(
	new InterleavedAttribute( { *SingleVertexAttribute.get(),
								*SingleNormalAttribute.get(),
								*SingleColorByteAttribute.get() } ) );

} // namespace Core

#endif