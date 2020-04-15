/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "renderer.h"

namespace Game
{

void Renderer::loadShaders()
{
	m_chunkShader.compileShaderFromFile( "voxelstructure.vert", Core::ShaderProgram::VERTEX_SHADER )
		.compileShaderFromFile( "voxelstructure.frag", Core::ShaderProgram::FRAGMENT_SHADER )
		.link();
}

void Renderer::render( World& world )
{
	m_chunkShader.bind();
	m_chunkShader.setUniform( "u_projection", m_projection );
	m_chunkShader.setUniform( "u_view", m_view );
	m_chunkShader.setUniform( "u_ambientLightPower", 0.8f );
	m_chunkShader.setUniform( "u_directionalLightPosition",
							  glm::vec3{ 5000.0f, -100000.0f, 14400.0f } );
	m_chunkShader.setUniform( "u_skyColor", glm::vec3( 179 / 255.0f, 210 / 255.0f, 238 / 255.0f ) );
	m_chunkShader.setUniform( "u_density", 0.004f );

	for( auto& chunkIt : world.getAllChunks() )
	{
		if( chunkIt.expired() )
		{
			continue;
		}

		std::shared_ptr< RenderWorldChunk > chunk
			= std::static_pointer_cast< RenderWorldChunk >( chunkIt.lock() );

		chunk->uploadWhenNeeded();
		if( !chunk->isMeshGenerated() || chunk->getMillisecondsNotSeen() > 0
			|| chunk->getAttributeBuffer().getVerticeAmount() == 0 )
		{
			continue;
		}

		m_chunkShader.setUniform( "u_transformation", chunk->getMatrix() );

		chunk->getAttributeBuffer().bind( 0 );
		glDrawArrays( GL_TRIANGLES, 0, chunk->getAttributeBuffer().getVerticeAmount() );
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