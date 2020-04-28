/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_GIZMO_RENDERER_H
#define CUBIX_GIZMO_RENDERER_H

#include "core/data/color.h"
#include "core/math/transform.h"
#include "core/opengl/attributebuffer.h"

#include "game/rendering/sub_renderer.h"

#include <memory>

namespace Core
{
class ShaderProgram;
}

namespace Game
{

class Renderer;

class GizmoRenderer : public SubRenderer
{
protected:
	struct RenderEntry
	{
		Core::AttributeBuffer& buffer;
		Core::Color color;
		Core::Transform transform;
	};

protected:
	Core::AttributeBuffer m_cubeAttributeBuffer;

	std::list< RenderEntry > m_toRender;

	std::shared_ptr< Core::ShaderProgram > m_shader;
	int m_colorUniformLocation;

public:
	GizmoRenderer( Renderer& renderer );

	void renderCube( Core::Transform& transform,
					 const Core::Color& color = Core::Color{ 0, 255, 0, 255 } );

	void finalize() override;
};

} // namespace Game

#endif
