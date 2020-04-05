/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "color.h"

#include <algorithm>

namespace Core
{

Color::Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a )
	: glm::tvec4< unsigned char >( r, g, b, a )
{
}

void Color::toFloat( glm::vec4& buffer ) const
{
	static const float multiplier = 1.0f / 255.0f;
	buffer.r					  = r * multiplier;
	buffer.g					  = g * multiplier;
	buffer.b					  = b * multiplier;
	buffer.a					  = a * multiplier;
}

glm::vec4 Color::toFloat() const
{
	static const float multiplier = 1.0f / 255.0f;
	return glm::vec4( r * multiplier, g * multiplier, b * multiplier, a * multiplier );
}

void Color::add( int r, int g, int b, int a )
{
	this->r = static_cast< unsigned char >( std::max( 0, std::min( 255, r + this->r ) ) );
	this->g = static_cast< unsigned char >( std::max( 0, std::min( 255, g + this->g ) ) );
	this->b = static_cast< unsigned char >( std::max( 0, std::min( 255, b + this->b ) ) );
	this->a = static_cast< unsigned char >( std::max( 0, std::min( 255, a + this->a ) ) );
}

} // namespace Core