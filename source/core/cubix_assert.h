/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_ASSERT_H
#define CUBIX_CUBIX_ASSERT_H

#include "cubix_log.h"
#include "defines.h"

#if CUBIX_ENABLE_ASSERT
#include <cstring>
#define __FILENAME__ ( strrchr( __FILE__, '\\' ) ? strrchr( __FILE__, '\\' ) + 1 : __FILE__ )
#define cubix_assert( expr, msg )                             \
	do                                                        \
	{                                                         \
		if( !( expr ) )                                       \
		{                                                     \
			__M_assert( #expr, __FILENAME__, __LINE__, msg ); \
		}                                                     \
	} while( false )

#define cubix_log_or_assert( expr, successful, error )          \
	do                                                          \
	{                                                           \
		if( !( expr ) )                                         \
		{                                                       \
			__M_assert( #expr, __FILENAME__, __LINE__, error ); \
		}                                                       \
		else                                                    \
		{                                                       \
			Core::Logger::Log( successful );                    \
		}                                                       \
	} while( false )
#else
#define cubix_assert( expr, msg ) \
	do                            \
	{                             \
		expr;                     \
	} while( false )
#define cubix_log_or_assert( expr, successful, error ) \
	do                                                 \
	{                                                  \
		expr;                                          \
	} while( false )
#endif

void __M_assert( const char* expressionStr, const char* file, int line, const char* message );
void __M_assert( const char* expressionStr,
				 const char* file,
				 int line,
				 const std::string& message );

#endif // CUBIX_CUBIX_ASSERT_H
