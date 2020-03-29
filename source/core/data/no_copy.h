/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_NO_COPY_H
#define CUBIX_NO_COPY_H

namespace Core
{

struct NoCopy
{
	NoCopy()					  = default;
	NoCopy( const NoCopy& other ) = delete;
	NoCopy& operator=( const NoCopy& other ) = delete;
};

} // namespace Core

#endif // CUBIX_NO_COPY_H
