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
	m_gameTime.setFPSLimit( 140 );
	connect( "127.0.0.1", 4444 );
	m_renderer.loadShaders();
	m_moveableView.setSpeed( 3 );
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

	int range = 6;
	for( int x = -range; x <= range; ++x )
	{
		for( int z = -range; z <= range; ++z )
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

} // namespace Game