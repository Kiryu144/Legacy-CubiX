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

#ifndef CUBIX_CUBIX_ASSERT_H
#define CUBIX_CUBIX_ASSERT_H

#ifdef CUBIX_DEBUG
#include <cstring>
#define __FILENAME__ ( strrchr( __FILE__, '\\' ) ? strrchr( __FILE__, '\\' ) + 1 : __FILE__ )
#define cubix_assert( expr, msg ) __M_assert( #expr, expr, __FILENAME__, __LINE__, msg )
#else
#define cubix_assert( expr, msg ) ;
#endif

void __M_assert(
	const char* expressionStr, bool expression, const char* file, int line, const char* message );

#endif // CUBIX_CUBIX_ASSERT_H
