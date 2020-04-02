/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_MEMORY_H
#define CUBIX_MEMORY_H

#include <memory>

namespace Core
{

template< typename T >
struct MemoryPointerAddressCompare
{
	bool operator()( const T& ptr1, const T& ptr2 )
	{
		return ptr1.get() < ptr2.get();
	}
};

template< typename T >
struct WeakMemoryPointerAddressCompare
{
	bool operator()( const T& ptr1, const T& ptr2 )
	{
		return ptr1.lock().get() < ptr2.lock().get();
	}
};

template< typename T >
using UniquePointerAdressCompare = MemoryPointerAddressCompare< std::unique_ptr< T > >;

template< typename T >
using SharedPointerAdressCompare = MemoryPointerAddressCompare< std::shared_ptr< T > >;

template< typename T >
using WeakPointerAdressCompare = WeakMemoryPointerAddressCompare< std::weak_ptr< T > >;

} // namespace Core

#endif // CUBIX_MEMORY_H
