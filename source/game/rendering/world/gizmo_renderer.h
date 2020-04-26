/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_GIZMO_RENDERER_H
#define CUBIX_GIZMO_RENDERER_H

#include "core/data/color.h"
#include "core/math/transform.h"
#include "core/opengl/attributebuffer.h"

#include <memory>

namespace Core
{
class ShaderProgram;
}

namespace Game
{

class Renderer;

class GizmoRenderer
{
protected:
	Renderer& m_renderer;
	Core::AttributeBuffer m_cubeAttributeBuffer;

	std::shared_ptr< Core::ShaderProgram > m_shader;
	int m_colorUniformLocation;

public:
	GizmoRenderer( Renderer& renderer );

	void drawCube( Core::Transform& transform,
				   const Core::Color& color = Core::Color{ 0, 255, 0, 255 } );
};

} // namespace Game

#endif
