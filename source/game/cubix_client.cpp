/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_client.h"

#include "core/logic/string_cast.h"
#include "core/opengl/opengl_context.h"
#include "core/opengl/shader_program.h"

#include "game/packet/packet_client_information.h"
#include "game/packet/packet_server_information.h"
#include "game/player_controller.h"
#include "game/rendering/world/block_outline_renderer.h"
#include "game/rendering/world/gizmo_renderer.h"
#include "game/rendering/world/world_chunk_renderer.h"
#include "game/world/chunk/chunk_worker.h"
#include "game/world/chunk/render_world_chunk.h"
#include "game/world/chunk/world_chunk.h"
#include "game/world/entity/entity.h"
#include "game/world/entity/player.h"

#include <glfw/glfw3.h>
#include <imgui/imgui.h>

namespace Game
{

CubixClient::CubixClient() : m_window( 1440, 900, "CubiX" )
{
	setWindowTitle();
	m_window.setVSync( false );
	m_gameTime.setFPSLimit( static_cast< unsigned int >( -1 ) );
	m_world.setRenderer( &m_renderer );

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

	m_renderer.initializeSubRenderers();

	connect( "127.0.0.1", 4444 );
	m_moveableView.setSpeed( 18000 );
	m_moveableView.setActive( false );

	std::shared_ptr< Player > player( new Player() );
	player->getPosition() = glm::vec3( 0.0f, 35.0f, 0.0f );
	m_world.summonEntity( player );
	m_playerController.reset( new PlayerController( player ) );
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

	m_moveableView.update( m_gameTime.getDeltaTime() );

	auto raycastHit
		= m_world.raycastBlocks( m_moveableView.getPosition(), m_moveableView.getDirection(), 24 );
	if( raycastHit.has_value() )
	{
		m_renderer.getBlockOutlineRenderer()->render( raycastHit.value(), { 0, 0, 0, 160 } );
	}

	for( auto& chunk : m_world.getAllChunks() )
	{
		m_renderer.getWorldChunkRenderer()->render(
			std::dynamic_pointer_cast< RenderWorldChunk >( chunk ) );
	}

	glm::ivec3 playerChunkPos{ WorldChunk::ChunkPosFromWorldPos( m_moveableView.getPosition() ) };
	for( int x = -m_viewDistance; x <= m_viewDistance; ++x )
	{
		for( int z = -m_viewDistance; z <= m_viewDistance; ++z )
		{
			glm::ivec2 chunkPos{ playerChunkPos.x + x, playerChunkPos.z + z };
			double distance{ std::sqrt(
				std::pow( static_cast< float >( chunkPos.x ) - playerChunkPos.x, 2 )
				+ std::pow( static_cast< float >( chunkPos.y ) - playerChunkPos.z, 2 ) ) };
			if( distance <= m_viewDistance )
			{
				m_world.updateForPlayer( chunkPos );
			}
		}
	}

	if( m_moveableView.getActive() )
	{
		m_renderer.setView( m_moveableView.getViewMatrix() );
	}
	else if( m_playerController.get() != nullptr )
	{
		m_playerController->updateView();
		m_renderer.setView( m_playerController->getView().getViewMatrix() );
	}
	m_renderer.setView( m_moveableView.getViewMatrix() );

	// m_playerController->update( m_gameTime.getDeltaTime() );

	m_renderer.finalizeSubRenderer();

#if CUBIX_IMGUI
	bool active = true;
	ImGui::Begin( "Debug Information", &active );
	ImGui::Text( "FPS: %d", int( m_gameTime.getFPS() ) );
	ImGui::Text( "Chunks loaded: %d", m_world.getAllChunks().size() );
	ImGui::Text( "Chunk queue: %d", m_world.getChunkWorker().size() );
	ImGui::SliderInt( "View Distance", &m_viewDistance, 2, 64 );
	ImGui::Text( "Position: %d %d %d",
				 static_cast< int >( m_moveableView.getPosition().x ),
				 static_cast< int >( m_moveableView.getPosition().y ),
				 static_cast< int >( m_moveableView.getPosition().z ) );
	ImGui::Text( "Chunk Position: %d %d %d",
				 static_cast< int >(
					 std::floor( m_moveableView.getPosition().x / WorldChunk::GetSideLength() ) ),
				 static_cast< int >(
					 std::floor( m_moveableView.getPosition().y / WorldChunk::GetSideLength() ) ),
				 static_cast< int >(
					 std::floor( m_moveableView.getPosition().z / WorldChunk::GetSideLength() ) ) );
	if( ImGui::Button( m_voxelMemoryConsumption.c_str() ) )
	{
		m_voxelMemoryConsumption = "Total Voxel Memory: "
			+ Core::ByteSizeToString( m_world.calculateVoxelMemoryConsumption() );
	}
	ImGui::End();
#endif
}

void CubixClient::onPacketReceive( Core::PeerID id, std::istream& istream )
{
	PacketType type;
	istream.read( reinterpret_cast< char* >( &type ), sizeof( decltype( type ) ) );

	switch( type )
	{
	case PacketType::CLIENTBOUND_SERVER_INFORMATION:
		PacketServerInformation packetServerInformation( "" );
		packetServerInformation.deserialize( istream );
		Core::Logger::Log( std::string( "Connected to " )
						   + packetServerInformation.getName().get() );
		PacketClientInformation packetClientInformation( "Kiryu" );
		send( id, &packetClientInformation );
		break;
	}
}

void CubixClient::onEvent( const Core::EventWindowResize& eventType )
{
	glm::mat4 projection = glm::perspective(
		glm::radians( 70.0f ), static_cast< float >( eventType.w ) / eventType.h, 0.1f, 1000.0f );
	m_renderer.setProjection( projection );
}

void CubixClient::onEvent( const Core::UserInputHandler::EventUpdate& eventType )
{
	if( eventType.instance.isKeyDown( Core::UserInputHandler::F ) )
	{
		std::shared_ptr< Entity > entity( new Entity() );
		entity->getPosition() = m_moveableView.getPosition();
		entity->setVelocity( m_moveableView.getDirection() * glm::vec3( 50.0f ) );
		m_world.summonEntity( entity );
	}

	if( eventType.instance.isKeyDown( Core::UserInputHandler::MOUSE_1 ) )
	{
		auto raycastHit = m_world.raycastBlocks(
			m_moveableView.getPosition(), m_moveableView.getDirection(), 100 );
		if( raycastHit.has_value() )
		{
			m_world.setVoxel( raycastHit.value(), {} ); // Remove voxel
			auto chunk = m_world.getChunk( WorldChunk::ChunkPosFromWorldPos( raycastHit.value() ) );
			auto renderChunk = static_cast< RenderWorldChunk* >( chunk.get() );
			m_world.getChunkWorker().queue( chunk, ChunkWorker::GENERATE_MESH );
		}
	}
}

void CubixClient::onEvent( const Core::EventWindowFileDrop& eventType )
{
	// m_group.reset( new VoxelGroup( eventType.fpath ) );
}

void CubixClient::setWindowTitle()
{
	std::string windowTitle{ "CubiX " + Defines::s_version };
#ifndef NDEBUG
	windowTitle += " (debug build)";
#endif
#ifdef CUBIX_ENABLE_ASSERT
	windowTitle += " (asserts)";
#endif
	m_window.setTitle( windowTitle );
}

} // namespace Game