/*
 * Copyright (c) 2020 David Klostermann.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
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