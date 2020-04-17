/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_SINGELTON_H
#define CUBIX_SINGELTON_H

namespace Core
{

template< typename T >
class Singelton
{
protected:
	Singelton() = default;

public:
	static T& Get()
	{
		static T instance;
		return instance;
	}
};

} // namespace Core

#endif // CUBIX_SINGELTON_H
