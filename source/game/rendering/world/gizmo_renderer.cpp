/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "gizmo_renderer.h"

#include "core/opengl/data/single_attribute.h"
#include "core/opengl/shader_program.h"

#include "game/rendering/renderer.h"

namespace Game
{

GizmoRenderer::GizmoRenderer( Renderer& renderer )
	: SubRenderer( renderer ), m_cubeAttributeBuffer( Core::SingleVertexAttribute )
{
	m_shader			   = renderer.getShaderRegistry().getValue( "gizmo_shader" );
	m_colorUniformLocation = m_shader->getUniformLocation( "u_color" );

	static const std::vector< glm::vec3 > s_cubeVertices{
		glm::vec3( 0, 0, 0 ), glm::vec3( 1, 0, 0 ), glm::vec3( 1, 1, 0 ), glm::vec3( 0, 1, 0 ),
		glm::vec3( 0, 0, 0 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 0, 1 ), glm::vec3( 0, 1, 1 ),
		glm::vec3( 0, 1, 0 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 0, 1 ), glm::vec3( 1, 0, 1 ),
		glm::vec3( 1, 1, 1 ), glm::vec3( 0, 1, 1 ), glm::vec3( 0, 0, 1 ), glm::vec3( 1, 0, 1 ),
		glm::vec3( 1, 1, 1 ), glm::vec3( 1, 1, 0 ), glm::vec3( 1, 0, 0 ), glm::vec3( 1, 0, 1 ),
	};
	m_cubeAttributeBuffer.upload( &s_cubeVertices[ 0 ], s_cubeVertices.size() );
}

void GizmoRenderer::renderCube( Core::Transform& transform, const Core::Color& color )
{
	m_toRender.push_back( { m_cubeAttributeBuffer, color, transform } );
}

void GizmoRenderer::finalize()
{
	m_shader->bind();

	m_shader->setUniform( m_shader->getProjectionUniform(), m_renderer.getProjection() );
	m_shader->setUniform( m_shader->getViewUniform(), m_renderer.getView() );

	for( auto& entry : m_toRender )
	{
		entry.buffer.bind( 0 );

		m_shader->setUniform( m_colorUniformLocation, entry.color.toFloat() );
		m_shader->setUniform( m_shader->getTransformUniform(), entry.transform.getMatrix() );

		glDrawArrays( GL_LINE_STRIP, 0, entry.buffer.getVerticeAmount() );
	}
	m_toRender.clear();
}

} // namespace Game