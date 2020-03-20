/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_OPENG_ERROR_H
#define CUBIX_OPENG_ERROR_H

#include "core/cubix_assert.h"

#ifdef CUBIX_DEBUG

#define gl_clear_error()      \
	do                        \
	{                         \
		__M_gl_clear_error(); \
	} while( false )

#define gl_log_error( gl_call )       \
	gl_call;                          \
	do                                \
	{                                 \
		__M_gl_log_error( #gl_call ); \
	} while( false )

#else
#define gl_log_error( gl_call ) gl_call
#define gl_clear_error()      \
	do                        \
	{                         \
		__M_gl_clear_error(); \
	} while( false )
#endif

void __M_gl_clear_error();
void __M_gl_log_error( const char* expr );

#endif // CUBIX_OPENG_ERROR_H
