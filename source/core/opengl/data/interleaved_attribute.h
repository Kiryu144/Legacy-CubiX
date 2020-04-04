/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_INTERLEAVED_ATTRIBUTE_H
#define CUBIX_INTERLEAVED_ATTRIBUTE_H

#include "core/opengl/data/single_attribute.h"

#include <vector>

namespace Core
{

class InterleavedAttribute : public Attribute
{
protected:
	std::vector< SingleAttribute > m_attributes;
	size_t m_stride;

public:
	InterleavedAttribute( const std::initializer_list< SingleAttribute >& attributes );

	CUBIX_GET_CR( m_attributes, Attributes );

	void vertexAttribPointer( unsigned int index ) override;
	size_t getSize( unsigned int multiplier ) override;
};

static const std::shared_ptr< InterleavedAttribute > InterleavedVertNormColAttribute(
	new InterleavedAttribute( { *SingleVertexAttribute.get(),
								*SingleNormalAttribute.get(),
								*SingleColorByteAttribute.get() } ) );

static const std::shared_ptr< InterleavedAttribute > InterleavedVertNormAttribute(
	new InterleavedAttribute( { *SingleVertexAttribute.get(), *SingleNormalAttribute.get() } ) );

static const std::shared_ptr< InterleavedAttribute > InterleavedVertColAttribute(
	new InterleavedAttribute( { *SingleVertexAttribute.get(), *SingleColorByteAttribute.get() } ) );

} // namespace Core

#endif
