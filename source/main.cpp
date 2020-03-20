/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "core/opengl/window.h"
#include "core/opengl/shader_program.h"

int main()
{
	Core::Window window( 1440, 900, "Cubix" );

	Core::ShaderProgram shaderProgram;
	shaderProgram.compileShaderFromFile( "3dcube.frag", Core::ShaderProgram::FRAGMENT_SHADER )
		.compileShaderFromFile( "3dcube.vert", Core::ShaderProgram::VERTEX_SHADER )
		.link();

	while( !window.shouldClose() )
	{
		Core::Window::Update();
	}

	return 0;
}
