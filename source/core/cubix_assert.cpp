/*
 * Copyright (c) 2020 David Klostermann.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 */

#include "cubix_assert.h"

#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

void __M_assert(
	const char* expressionStr, bool expression, const char* file, int line, const char* message )
{
	if( !expression )
	{
		std::stringstream text;
		text << "File: " << file << ":" << line << std::endl;
		text << "Expression: " << expressionStr << std::endl;
		text << "Message: " << message;
		std::string str = text.str();

		std::cerr << "Cubix Assertion" << std::endl << str << std::endl;

#ifdef _WIN32
		MessageBox( nullptr, str.c_str(), "Cubix Assertion", MB_OK );
#endif
		abort();
	}
}
