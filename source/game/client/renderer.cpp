/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "renderer.h"

#include "game/common/world/world_chunk.h"

namespace Game
{

void Renderer::loadShaders()
{
	m_chunkShader.compileShaderFromFile( "basic.vert", Core::ShaderProgram::VERTEX_SHADER )
		.compileShaderFromFile( "basic.frag", Core::ShaderProgram::FRAGMENT_SHADER )
		.link();
}

void Renderer::render( World& world )
{
	m_chunkShader.bind();
	m_chunkShader.setUniform( "u_projection", m_projection );
	m_chunkShader.setUniform( "u_view", m_view );
	m_chunkShader.setUniform( "u_ambientLightPower", 0.8f );
	m_chunkShader.setUniform( "u_directionalLightPower", 1.0f );
	m_chunkShader.setUniform( "u_directionalLightPosition",
							  glm::vec3{ 5000.0f, -100000.0f, 14400.0f } );

	for( auto& chunkIt : world.getAllChunk() )
	{
		if( chunkIt.expired() )
		{
			continue;
		}

		auto chunk = chunkIt.lock();
		std::lock_guard< std::mutex > guard( *chunk );

		chunk->upload();

		if( chunk->getVertices().getVerticeAmount() == 0 )
		{
			continue;
		}

		m_chunkShader.setUniform( "u_transformation", chunk->getMatrix() );

		chunk->getVertices().bind( 0 );
		chunk->getNormals().bind( 1 );
		chunk->getColors().bind( 2 );

		glDrawArrays( GL_TRIANGLES, 0, chunk->getVertices().getVerticeAmount() );
	}
}

void Renderer::setView( const glm::mat4& view )
{
	m_view = view;
}

void Renderer::setProjection( const glm::mat4& projection )
{
	m_projection = projection;
}

} // namespace Game