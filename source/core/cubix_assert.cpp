/*
 * Copyright (c) 2020 David Klostermann.
 */
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
