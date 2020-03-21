/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "core/opengl/shader_program.h"
#include "core/opengl/attributebuffer.h"
#include "core/opengl/window.h"

int main()
{
	Core::Window window( 1440, 900, "Cubix" );

	Core::ShaderProgram shader;
	shader.compileShaderFromFile( "3dcube.vert", Core::ShaderProgram::VERTEX_SHADER )
		.compileShaderFromFile( "3dcube.frag", Core::ShaderProgram::FRAGMENT_SHADER )
		.link();

	glm::vec3 vertices[]
		= { { -0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, -0.5f },
			{ 0.5f, 0.5f, -0.5f },	 { -0.5f, 0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f },
			{ -0.5f, -0.5f, 0.5f },	 { 0.5f, -0.5f, 0.5f },	 { 0.5f, 0.5f, 0.5f },
			{ 0.5f, 0.5f, 0.5f },	 { -0.5f, 0.5f, 0.5f },	 { -0.5f, -0.5f, 0.5f },
			{ -0.5f, 0.5f, 0.5f },	 { -0.5f, 0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f },
			{ -0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, 0.5f }, { -0.5f, 0.5f, 0.5f },
			{ 0.5f, 0.5f, 0.5f },	 { 0.5f, 0.5f, -0.5f },	 { 0.5f, -0.5f, -0.5f },
			{ 0.5f, -0.5f, -0.5f },	 { 0.5f, -0.5f, 0.5f },	 { 0.5f, 0.5f, 0.5f },
			{ -0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, 0.5f },
			{ 0.5f, -0.5f, 0.5f },	 { -0.5f, -0.5f, 0.5f }, { -0.5f, -0.5f, -0.5f },
			{ -0.5f, 0.5f, -0.5f },	 { 0.5f, 0.5f, -0.5f },	 { 0.5f, 0.5f, 0.5f },
			{ 0.5f, 0.5f, 0.5f },	 { -0.5f, 0.5f, 0.5f },	 { -0.5f, 0.5f, -0.5f } };

	shader.bind();

	Core::AttributeBuffer buffer( GL_ARRAY_BUFFER, Core::StandardVertexAttribute );
	buffer.upload< glm::vec3 >( &vertices[ 0 ], 36 );
	buffer.bind( 0 );

	while( !window.shouldClose() )
	{
		Core::Window::Update();
		window.swap();

		glDrawArrays( GL_TRIANGLES, 0, 36 );
	}

	return 0;
}
