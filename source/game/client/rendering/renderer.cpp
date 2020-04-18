/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "renderer.h"

namespace Game
{

/*
void Renderer::render( World& world )
{
	m_chunkShader.bind();
	m_chunkShader.setUniform( "u_projection", m_projection );
	m_chunkShader.setUniform( "u_view", m_view );
	m_chunkShader.setUniform( "u_ambientLightPower", 0.8f );
	m_chunkShader.setUniform( "u_directionalLightPosition",
							  glm::vec3{ 5000.0f, -100000.0f, 14400.0f } );
	m_chunkShader.setUniform( "u_skyColor", glm::vec3( 179 / 255.0f, 210 / 255.0f, 238 / 255.0f ) );
	m_chunkShader.setUniform( "u_density", 0.0004f );

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
*/

void Renderer::render( Renderable* renderable )
{
	if( !renderable )
	{
		return;
	}

	auto shader	 = m_shaderRegistry.getValue( renderable->getShader() );
	auto& attrib = renderable->getAttributeBuffer();

	if( attrib.getVerticeAmount() == 0 )
	{
		return;
	}

	shader->bind();

	if( shader->getProjectionUniform() >= 0 )
	{
		shader->setUniform( shader->getProjectionUniform(), m_projection );
	}

	if( shader->getProjectionUniform() >= 0 )
	{
		shader->setUniform( shader->getViewUniform(), m_view );
	}

	renderable->setUniforms( *shader );
	attrib.bind( 0 );

	glDrawArrays( renderable->getDrawMode(), 0, attrib.getVerticeAmount() );
}

} // namespace Game