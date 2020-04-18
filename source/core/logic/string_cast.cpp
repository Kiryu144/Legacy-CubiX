/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "string_cast.h"

namespace Core
{

std::string ByteSizeToString( size_t size )
{
	static const size_t kilo = 1024;
	static const size_t mega = kilo * 1024;
	static const size_t giga = mega * 1024;

	if( size / giga )
	{
		return Core::to_string( static_cast< float >( size ) / giga, 2 ) + "GB";
	}

	if( size / mega )
	{
		return Core::to_string( static_cast< float >( size ) / mega, 2 ) + "MB";
	}

	if( size / kilo )
	{
		return Core::to_string( static_cast< float >( size ) / kilo, 2 ) + "KB";
	}

	return size + "B";
}

} // namespace Core