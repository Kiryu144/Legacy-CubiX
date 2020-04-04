/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_client.h"

#include "game/common/packet/packet_client_information.h"
#include "game/common/packet/packet_server_information.h"
#include "game/common/world/world_chunk.h"

#include <glfw/glfw3.h>
#include <imgui/imgui.h>

namespace Game
{

CubixClient::CubixClient() : m_window( 1440, 900, "CubiX" )
{
	m_gameTime.setFPSLimit( 10000 );
	connect( "127.0.0.1", 4444 );
	m_renderer.loadShaders();
	m_moveableView.setSpeed( 3 );

	glDisable( GL_CULL_FACE );

	m_clipboard.createSphere( 64, { 255, 64, 128 } );
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

	for( int x = -m_viewDistance; x <= m_viewDistance; ++x )
	{
		for( int z = -m_viewDistance; z <= m_viewDistance; ++z )
		{
			m_world.updateForPlayer(
				{ x + m_moveableView.getPosition().x / WorldChunk::s_sideLength,
				  z + m_moveableView.getPosition().z / WorldChunk::s_sideLength } );
		}
	}

	m_moveableView.update( m_gameTime.getDeltaTime() );
	m_renderer.setView( m_moveableView.getViewMatrix() );
	m_renderer.render( m_world );

#if CUBIX_IMGUI
	bool active = true;
	ImGui::Begin( "Debug Information", &active );
	ImGui::Text( "FPS: %d", int( m_gameTime.getFPS() ) );
	ImGui::Text( "Chunks loaded: %d", m_world.getAllChunks().size() );
	ImGui::Text( "Chunk queue: %d", m_world.getChunkWorker().size() );
	ImGui::SliderInt( "View Distance", &m_viewDistance, 2, 16 );
	ImGui::Text( "Position: %d %d %d",
				 static_cast< int >( m_moveableView.getPosition().x ),
				 static_cast< int >( m_moveableView.getPosition().y ),
				 static_cast< int >( m_moveableView.getPosition().z ) );
	ImGui::Text( "Chunk Position: %d %d %d",
				 static_cast< int >(
					 std::floor( m_moveableView.getPosition().x / WorldChunk::s_sideLength ) ),
				 static_cast< int >(
					 std::floor( m_moveableView.getPosition().y / WorldChunk::s_sideLength ) ),
				 static_cast< int >(
					 std::floor( m_moveableView.getPosition().z / WorldChunk::s_sideLength ) ) );
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
	if( eventType.instance.isKeyDown( Core::UserInputHandler::F ) && m_group.get() != nullptr )
	{
		m_world.insert( *m_group, m_moveableView.getPosition() );
	}

	if( eventType.instance.isKeyDown( Core::UserInputHandler::R ) )
	{
		m_moveableView.getPosition() += glm::vec3{ 5000, 0, 5000 };
	}
}

void CubixClient::onEvent( const Core::EventWindowFileDrop& eventType )
{
	m_group.reset( new VoxelGroup( eventType.fpath ) );
}

} // namespace Game