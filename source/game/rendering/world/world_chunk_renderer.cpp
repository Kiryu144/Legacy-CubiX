/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_renderer.h"

#include "core/opengl/shader_program.h"

#include "game/rendering/renderer.h"
#include "game/world/chunk/render_world_chunk.h"

namespace Game
{

WorldChunkRenderer::WorldChunkRenderer( Renderer& renderer ) : SubRenderer( renderer )
{
	m_shader				   = renderer.getShaderRegistry().getValue( "world_chunk" );
	m_ambientLightPowerUniform = m_shader->getUniformLocation( "u_ambientLightPower" );
	m_directionalLightPositionUniform
		= m_shader->getUniformLocation( "u_directionalLightPosition" );
	m_skyColorUniform	= m_shader->getUniformLocation( "u_skyColor" );
	m_fogDensityUniform = m_shader->getUniformLocation( "u_density" );
}

void WorldChunkRenderer::render( std::shared_ptr< RenderWorldChunk > chunk )
{
	if( chunk != nullptr )
	{
		m_chunks.push_back( chunk );
	}
}

void WorldChunkRenderer::finalize()
{
	m_shader->bind();
	m_shader->setUniform( m_shader->getProjectionUniform(), m_renderer.getProjection() );
	m_shader->setUniform( m_shader->getViewUniform(), m_renderer.getView() );
	m_shader->setUniform( m_ambientLightPowerUniform, 0.8f );
	m_shader->setUniform( m_directionalLightPositionUniform,
						  glm::vec3{ 5000.0f, -100000.0f, 14400.0f } );
	m_shader->setUniform( m_skyColorUniform,
						  glm::vec3( 179 / 255.0f, 210 / 255.0f, 238 / 255.0f ) );
	m_shader->setUniform( m_fogDensityUniform, 0.0004f );

	for( auto& chunk : m_chunks )
	{
		chunk->uploadWhenNeeded();
		if( chunk->getAttributeBuffer().isValid() )
		{
			m_shader->setUniform( m_shader->getTransformUniform(), chunk->getMatrix() );
			chunk->getAttributeBuffer().bind( 0 );
			int vertices = chunk->getAttributeBuffer().getVerticeAmount();
			glDrawArrays( GL_TRIANGLES, 0, chunk->getAttributeBuffer().getVerticeAmount() );
		}
	}

	m_chunks.clear();
}

} // namespace Game