/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_COLOR_H
#define CUBIX_COLOR_H

#include <glm/vec4.hpp>

namespace Core
{

class Color : public glm::tvec4< unsigned char >
{
public:
	Color( unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 0 );

	void toFloat( glm::vec4& buffer ) const;
	glm::vec4 toFloat() const;
};

} // namespace Core

#endif
