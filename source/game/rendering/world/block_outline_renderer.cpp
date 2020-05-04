/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "block_outline_renderer.h"

#include "core/math/transform.h"
#include "core/opengl/shader_program.h"

#include "game/rendering/renderer.h"

namespace Game
{

BlockOutlineRenderer::BlockOutlineRenderer( Renderer& renderer ) : SubRenderer( renderer )
{
	m_shader	   = renderer.getShaderRegistry().getValue( "block_outline" );
	m_uniformColor = m_shader->getUniformLocation( "u_color" );
}

void BlockOutlineRenderer::render( const glm::ivec3& blockPosition, const Core::Color& color )
{
	m_outlines.push_back( { blockPosition, color } );
}

void BlockOutlineRenderer::finalize()
{
	m_shader->bind();
	m_shader->setUniform( m_shader->getProjectionUniform(), m_renderer.getPerspectiveProjection() );
	m_shader->setUniform( m_shader->getViewUniform(), m_renderer.getView() );

	for( const auto& outline : m_outlines )
	{
		Core::Transform transform;
		transform.getPosition() += outline.position;
		m_shader->setUniform( m_shader->getTransformUniform(), transform.getMatrix() );
		m_shader->setUniform( m_uniformColor, outline.color.toFloat() );
		glDrawArrays( GL_LINE_STRIP, 0, 20 );
	}
	m_outlines.clear();
}

} // namespace Game