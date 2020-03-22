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

int main()
{
	Core::Window window( 1440, 900, "Cubix" );

	Core::ShaderProgram shader;
	shader.compileShaderFromFile( "basic.vert", Core::ShaderProgram::VERTEX_SHADER )
		.compileShaderFromFile( "basic.frag", Core::ShaderProgram::FRAGMENT_SHADER )
		.link();

	Game::VoxelGroup voxelGroup( { 16, 16, 16 } );

	for( int x = 0; x < 16; ++x )
	{
		for( int y = 0; y < 16; ++y )
		{
			for( int z = 0; z < 16; ++z )
			{
				if( rand() % 100 < 50 )
				{
					voxelGroup[ { x, y, z } ] = Game::FlagVoxel( 255, 0, 255, 255 );
				}
			}
		}
	}

	voxelGroup.generateMesh();

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

	Core::AttributeBuffer buffer( GL_ARRAY_BUFFER, Core::StandardVertexAttribute );
	buffer.upload< glm::vec3 >( &vertices[ 0 ], 36 );
	buffer.bind( 0 );

	// voxelGroup.getVertices().bind(0);

	glm::mat4 projection = glm::perspective(
		70.0f, static_cast< float >( window.getWidth() ) / window.getHeight(), 0.1f, 100.0f );
	glm::mat4 view( 1.0 );

	shader.bind();
	shader.setUniform( "projection", projection );
	shader.setUniform( "view", view );

	while( !window.shouldClose() )
	{
		Core::Window::Update();
		window.swap();

		for( int x = -1; x <= 1; ++x )
		{
			for( int y = -1; y <= 1; ++y )
			{
				for( int z = -1; z <= 1; ++z )
				{
					if( x == 0 && y == 0 && z == 0 )
					{
						continue;
					}
					glm::mat4 transformation = glm::translate(
						glm::mat4( 1.0f ), glm::vec3( x * 50.0f, y * 50.0f, z * 50.0f ) );
					shader.setUniform( "transformation", transformation );
					glDrawArrays( GL_TRIANGLES, 0, 36 );
				}
			}
		}
	}

	return 0;
}
