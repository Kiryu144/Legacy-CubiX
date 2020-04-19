/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_RENDERER_H
#define CUBIX_RENDERER_H

#include "core/cubix_macro.h"
#include "core/data/registry.h"

#include <glm/mat4x4.hpp>

namespace Core
{
class ShaderProgram;
}

namespace Game
{

class Renderable;
class GizmoRenderer;

class Renderer
{
public:
	typedef Core::Registry< std::shared_ptr< Core::ShaderProgram > > ShaderRegistry;

protected:
	ShaderRegistry m_shaderRegistry;

	glm::mat4 m_projection;
	glm::mat4 m_view;

	// Sub renderers
	std::shared_ptr< GizmoRenderer > m_gizmoRenderer;

public:
	CUBIX_GET_SET_CR_CR( m_projection, Projection );
	CUBIX_GET_SET_CR_CR( m_view, View );
	CUBIX_GET_R_CR( m_shaderRegistry, ShaderRegistry );
	CUBIX_GET_R_CR( m_gizmoRenderer, GizmoRenderer );

	// Helper
	std::shared_ptr< Core::ShaderProgram > createShader( const std::string& name );

	void initializeSubRenderers();
	void render( Renderable* renderable );
};

} // namespace Game

#endif
