/*
 * Copyright (c) 2020 David Klostermann.
 */

#include <core/opengl/shader_program.h>
#include "core/opengl/window.h"

int main()
{
	Core::Window window( 1440, 900, "Cubix" );

	Core::ShaderProgram shader;
	shader.compileShaderFromFile( "3dcube.vert", Core::ShaderProgram::VERTEX_SHADER )
		.compileShaderFromFile( "3dcube.frag", Core::ShaderProgram::FRAGMENT_SHADER )
		.link();

	while( !window.shouldClose() )
	{
		Core::Window::Update();
		window.swap();
	}

	return 0;
}
