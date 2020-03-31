/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_LOCKABLE_H
#define CUBIX_LOCKABLE_H

#include <mutex>

namespace Core
{

template< typename T, typename M = std::mutex >
struct Lockable : public T, public M
{
	std::lock_guard< M > lockGuard()
	{
		return std::lock_guard< M >( *this );
	}
};

} // namespace Core

#endif // CUBIX_LOCKABLE_H
