/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_client.h"

#include "core/logic/string_cast.h"
#include "core/opengl/opengl_context.h"
#include "core/opengl/shader_program.h"

#include "game/packet/packet_client_information.h"
#include "game/player/player_controller.h"
#include "game/rendering/world/block_outline_renderer.h"
#include "game/rendering/world/gizmo_renderer.h"
#include "game/rendering/world/world_chunk_renderer.h"
#include "game/world/chunk/world_chunk.h"
#include "game/world/entity/entity.h"
#include "game/world/entity/player.h"

#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>

namespace Game
{

CubixClient::CubixClient() : m_window( 1440, 900, "CubiX" )
{
	std::string windowTitle{ "CubiX " + Defines::s_version };
#ifndef NDEBUG
	windowTitle += " (debug build)";
#endif
#ifdef CUBIX_ENABLE_ASSERT
	windowTitle += " (asserts)";
#endif

	m_window.setTitle( windowTitle );
	m_window.setVSync( false );
	m_window.setMsaaSamples( 4 );
	m_gameTime.setFPSLimit( static_cast< unsigned int >( -1 ) );

	Core::OpenGLContext::Get().setClearColor( { 127, 170, 255, 255 } );

	m_renderer.createShader( "world_chunk" )
		->compileShaderFromFile( "shader\\world_chunk.vert" )
		.compileShaderFromFile( "shader\\world_chunk.frag" )
		.link();

	m_renderer.createShader( "gizmo_shader" )
		->compileShaderFromFile( "shader\\gizmo_shader.vert" )
		.compileShaderFromFile( "shader\\gizmo_shader.frag" )
		.link();

	m_renderer.createShader( "voxel_structure" )
		->compileShaderFromFile( "shader\\voxel_structure.vert" )
		.compileShaderFromFile( "shader\\voxel_structure.frag" )
		.link();

	m_renderer.createShader( "block_outline" )
		->compileShaderFromFile( "shader\\block_outline.vert" )
		.compileShaderFromFile( "shader\\block_outline.frag" )
		.link();

	m_renderer.createShader( "box" )
		->compileShaderFromFile( "shader\\box.vert" )
		.compileShaderFromFile( "shader\\box.frag" )
		.link();

	m_renderer.initializeSubRenderers();

	m_moveableView.setSpeed( 18 );
	m_moveableView.setMouseSensitivity( 0.1f );
	m_moveableView.setActive( false );

	std::shared_ptr< Player > player( new Player() );
	player->getPosition() = glm::vec3( 0.0f, 55.0f, 0.0f );
}

void CubixClient::update()
{
	Cubix::update();
	Core::Window::Update();
	m_window.swap();

	if( m_window.shouldClose() )
	{
		quit();
	}

	Core::Transform transform;
	m_renderer.getGizmoRenderer()->renderCube( transform );

	m_moveableView.update( m_gameTime.getDeltaTime() );

	m_renderer.setView( m_moveableView.getViewMatrix() );
	m_renderer.finalizeSubRenderer();

#ifdef CUBIX_IMGUI
	drawImGui();
#endif
}

void CubixClient::drawImGui()
{
#ifdef CUBIX_IMGUI
	static char serverAddress[ 32 ] = "127.0.0.1:4444";

	ImGui::Begin( "CubiX" );

	if( m_client.getConnected() )
	{
		if( ImGui::Button( "Disconnect" ) )
		{
			m_client.disconnect();
		}
	}
	else
	{
		ImGui::InputText( "Server Address", &serverAddress[ 0 ], 32 );
		if( ImGui::Button( "Connect" ) )
		{
			m_client.connect( serverAddress );
		}
	}
	ImGui::End();
#endif
}

void CubixClient::onEvent( const Core::EventWindowResize& event )
{
	m_renderer.setPerspectiveProjection( glm::perspective(
		glm::radians( 70.0f ), static_cast< float >( event.w ) / event.h, 0.1f, 1000.0f ) );
	m_renderer.setOrthogonalProjection(
		glm::ortho( 0, static_cast< int >( event.w ), 0, static_cast< int >( event.h ) ) );
}

} // namespace Game