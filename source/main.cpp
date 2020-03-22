/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "core/opengl/shader_program.h"
#include "core/opengl/attributebuffer.h"
#include "core/opengl/window.h"

#include "game/voxel/voxel_group.h"
#include "core/container/transform.h"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <GLFW/glfw3.h>

int main()
{
	Core::Window window( 1440, 900, "Cubix" );

	Core::ShaderProgram shader;
	shader.compileShaderFromFile( "basic.vert", Core::ShaderProgram::VERTEX_SHADER )
		.compileShaderFromFile( "basic.frag", Core::ShaderProgram::FRAGMENT_SHADER )
		.link();

	Game::VoxelGroup voxelGroup( { 16, 16, 16 } );

	glDisable( GL_CULL_FACE );

	for( int x = 0; x < 16; ++x )
	{
		for( int y = 0; y < 16; ++y )
		{
			for( int z = 0; z < 16; ++z )
			{
				if( rand() % 100 < 50 )
				{
					voxelGroup.set( { x, y, z }, { 128, 128, 64, 255 }, false );
				}
			}
		}
	}

	voxelGroup.updateAllFaces();
	voxelGroup.regenerateMesh();

	glm::mat4 projection = glm::perspective(
		70.0f, static_cast< float >( window.getWidth() ) / window.getHeight(), 0.1f, 100.0f );
	glm::mat4 view( 1.0 );

	Core::Transform transform;
	transform.getPosition() += glm::vec3( 0.0f, 0.0f, -45.0f );

	shader.bind();
	shader.setUniform( "projection", projection );
	shader.setUniform( "view", view );

	while( !window.shouldClose() )
	{
		Core::Window::Update();
		window.swap();

		transform.getRotation() = glm::vec3{ glfwGetTime() / 2.0f, glfwGetTime() / 4.0f, 0.0f };
		shader.setUniform( "transformation", transform.getMatrix() );

		voxelGroup.getVertices().bind( 0 );
		voxelGroup.getNormals().bind( 1 );
		voxelGroup.getColors().bind( 2 );
		glDrawArrays( GL_TRIANGLES, 0, voxelGroup.getVertices().getVerticeAmount() );
	}

	return 0;
}
