/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_BLOCK_OUTLINE_RENDERER_H
#define CUBIX_BLOCK_OUTLINE_RENDERER_H

#include "core/data/color.h"

#include "game/rendering/sub_renderer.h"

#include <list>
#include <memory>

#include <glm/vec3.hpp>

namespace Core
{
class ShaderProgram;
} // namespace Core

namespace Game
{

class BlockOutlineRenderer : public SubRenderer
{
protected:
	struct BlockOutline
	{
		glm::ivec3 position;
		Core::Color color;
	};

	std::list< BlockOutline > m_outlines;
	std::shared_ptr< Core::ShaderProgram > m_shader;

	int m_uniformColor;

public:
	BlockOutlineRenderer( Renderer& renderer );

	void render( const glm::ivec3& blockPosition, const Core::Color& color );
	void finalize() override;
};

} // namespace Game

#endif
