/*
 * Copyright (c) 2020 David Klostermann.
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
