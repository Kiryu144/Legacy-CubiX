/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_MACRO_H
#define CUBIX_CUBIX_MACRO_H

// Inline getter returns copy
#define CUBIX_GET_V( x, n ) \
	decltype( x ) get##n()  \
	{                       \
		return x;           \
	}

// Inline getter returns reference
#define CUBIX_GET_R( x, n ) \
	decltype( x )& get##n() \
	{                       \
		return x;           \
	}

// Inline getter returns const reference
#define CUBIX_GET_CR( x, n )            \
	const decltype( x )& get##n() const \
	{                                   \
		return x;                       \
	}

// Inline getter returns reference and const reference
#define CUBIX_GET_R_CR( x, n ) CUBIX_GET_R( x, n ) CUBIX_GET_CR( x, n )

// Inline setter that takes a const copy
#define CUBIX_SET_V( x, n )                \
	void set##n( const decltype( x ) _in ) \
	{                                      \
		x = _in;                           \
	}

// Inline setter that takes a const refrence
#define CUBIX_SET_CR( x, n )                \
	void set##n( const decltype( x )& _in ) \
	{                                       \
		x = _in;                            \
	}

// Inline getter & setter that take and return const references
#define CUBIX_GET_SET_R_CR( x, n ) CUBIX_GET_R_CR( x, n ) CUBIX_SET_CR( x, n )

// Inline getter & setter that take and return const references
#define CUBIX_GET_SET_CR_CR( x, n ) CUBIX_GET_CR( x, n ) CUBIX_SET_CR( x, n )

#endif // CUBIX_CUBIX_MACRO_H
