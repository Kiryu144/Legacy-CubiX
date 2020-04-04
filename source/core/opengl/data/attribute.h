/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_ATTRIBUTE_H
#define CUBIX_ATTRIBUTE_H

#include <vector>

namespace Core
{

class Attribute
{
public:
	virtual void vertexAttribPointer( unsigned int index ) = 0;
	virtual size_t getSize( unsigned int multiplier = 1 )  = 0;
};

} // namespace Core

#endif // CUBIX_ATTRIBUTE_H
