/*
 * Copyright (c) 2020 David Klostermann.
 */

#include <core/opengl/window.h>

int main(int argc, char** argv)
{
	Cubix::Core::Window window(std::string(argv[0]), {1440, 900}, Cubix::Core::Window::FLAG_RESIZEABLE);

	while (!window.shouldClose())
	{
		window.update();
	}

	return 0;
}