/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_STATIC_STRING_H
#define CUBIX_STATIC_STRING_H

#include <array>
#include <cstring>
#include <ostream>

namespace Core
{

template< size_t N >
class StaticString : public std::array< char, N >
{
private:
	char endingNull = 0;

public:
	StaticString( const std::string& str )
	{
		if( str.empty() )
		{
			return;
		}
		memcpy( this, &str.at( 0 ), std::min( str.size(), N ) );
	}

	StaticString( const char* str )
	{
		auto strlen = std::strlen( str );
		memcpy( this, str, std::min( strlen, N ) );
	}

	StaticString() = default;

	const char* get() const
	{
		return reinterpret_cast< const char* >( this );
	}

	size_t size() const
	{
		return strlen( get() );
	}

	friend std::ostream& operator<<( std::ostream& os, const StaticString& string )
	{
		os << string.get();
		return os;
	}
};

} // namespace Core

#endif
