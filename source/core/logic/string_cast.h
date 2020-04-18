/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_STRING_CAST_H
#define CUBIX_STRING_CAST_H

#include <sstream>
#include <string>

namespace Core
{

template< typename T >
std::string to_string( const T& value, const unsigned int precision = 99 )
{
	std::ostringstream out;
	out.precision( precision );
	out << std::fixed << value;
	return out.str();
}

std::string ByteSizeToString( size_t size );

} // namespace Core

#endif // CUBIX_STRING_CAST_H
