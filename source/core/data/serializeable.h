/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_SERIALIZEABLE_H
#define CUBIX_SERIALIZEABLE_H

#include <istream>
#include <ostream>

namespace Core
{

class Serializeable
{
public:
	virtual void serialize( std::ostream& out ) const = 0;
	virtual void deserialize( std::istream& in )	  = 0;
};

} // namespace Core

#endif
