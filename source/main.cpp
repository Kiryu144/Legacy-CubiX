/*
 * Copyright (c) 2020 David Klostermann.
 */

#define CUBIX_DEBUG

#include <iostream>
#include "core/cubix_assert.h"

int main()
{
	std::cout << "Hello, World!" << std::endl;

	cubix_assert( false, "This is wrooong!" );

	return 0;
}
