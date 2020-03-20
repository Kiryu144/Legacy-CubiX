/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "core/opengl/window.h"

int main()
{
	Core::Window window( 1440, 900, "Cubix" );

	while( !window.shouldClose() )
	{
		Core::Window::Update();
		window.swap();
	}

	return 0;
}
