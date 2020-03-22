/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_ATTRIBUTE_H
#define CUBIX_ATTRIBUTE_H

#include <glad/glad.h>

namespace Core
{

class Attribute;

class Attribute
{
protected:
	const GLenum m_dataType;	   // GL_FLOAT, GL_INT, etc ..
	const unsigned char m_scalars; // 1 - 4
	const bool m_normalize;

public:
	Attribute( GLenum dataType, unsigned char scalars, bool normalize );

	size_t getDataTypeSize() const;
	size_t getTotalSize( size_t nVertices = 1 ) const;

	const GLenum getDataType() const;
	const unsigned char getScalars() const;
	const bool getNormalize() const;
};

static const Attribute StandardVertexAttribute{ GL_FLOAT, 3, false };
static const Attribute StandardNormalAttribute{ GL_FLOAT, 3, false };
static const Attribute StandardColorByteAttribute{ GL_UNSIGNED_BYTE, 4, true };
static const Attribute StandardColorFloatAttribute{ GL_FLOAT, 4, false };

} // namespace Core

#endif
