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

	Game::VoxelGroup voxelGroup( "antenna.vox" );

	glDisable( GL_CULL_FACE );

	voxelGroup.updateAllFaces();
	voxelGroup.regenerateMesh();

	glm::mat4 projection = glm::perspective(
		70.0f, static_cast< float >( window.getWidth() ) / window.getHeight(), 0.1f, 1000.0f );
	glm::mat4 view( 1.0 );

	Core::Transform transform;
	transform.getPosition() += glm::vec3( 0.0f, 0.0f, -85.0f );

	shader.bind();
	shader.setUniform( "u_projection", projection );
	shader.setUniform( "u_view", view );
	shader.setUniform( "u_ambientLightPower", 0.6f );
	shader.setUniform( "u_directionalLightPower", 0.9f );
	shader.setUniform( "u_directionalLightPosition", { 1000.0f, 0.0f, 0.0f } );

	while( !window.shouldClose() )
	{
		Core::Window::Update();
		window.swap();

		transform.getRotation() = glm::vec3{ 0.0f, glfwGetTime() / 2.0f, 0.0f };
		shader.setUniform( "u_transformation", transform.getMatrix() );

		voxelGroup.getVertices().bind( 0 );
		voxelGroup.getNormals().bind( 1 );
		voxelGroup.getColors().bind( 2 );
		glDrawArrays( GL_TRIANGLES, 0, voxelGroup.getVertices().getVerticeAmount() );
	}

	return 0;
}
