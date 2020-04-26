/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "renderer.h"

#include "core/opengl/attributebuffer.h"
#include "core/opengl/shader_program.h"

#include "game/rendering/world/block_outline_renderer.h"
#include "game/rendering/world/gizmo_renderer.h"
#include "game/rendering/world/world_chunk_renderer.h"

namespace Game
{

void Renderer::initializeSubRenderers()
{
	m_gizmoRenderer.reset( new GizmoRenderer( *this ) );
	m_blockOutlineRenderer.reset( new BlockOutlineRenderer( *this ) );
	m_worldChunkRenderer.reset( new WorldChunkRenderer( *this ) );
}

std::shared_ptr< Core::ShaderProgram > Renderer::createShader( const std::string& name )
{
	std::shared_ptr< Core::ShaderProgram > shader( new Core::ShaderProgram() );
	m_shaderRegistry.insert( name, shader );
	return shader;
}

void Renderer::finalizeSubRenderer()
{
	m_blockOutlineRenderer->finalize();
	m_worldChunkRenderer->finalize();
}

} // namespace Game