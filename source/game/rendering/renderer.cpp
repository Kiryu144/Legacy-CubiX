/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "renderer.h"

#include "core/opengl/attributebuffer.h"
#include "core/opengl/shader_program.h"

#include "game/rendering/gizmo_renderer.h"
#include "game/rendering/renderable.h"

namespace Game
{

void Renderer::initializeSubRenderers()
{
	m_gizmoRenderer.reset( new GizmoRenderer( *this ) );
}

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