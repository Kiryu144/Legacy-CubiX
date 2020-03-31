/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_client.h"

#include "game/common/packet/packet_client_information.h"
#include "game/common/packet/packet_server_information.h"

namespace Game
{

CubixClient::CubixClient() : m_window( 1440, 900, "CubiX" )
{
	m_gameTime.setFPSLimit( 240 );
	connect( "127.0.0.1", 4444 );
	m_renderer.loadShaders();

	int range = 6;
	for( int x = -range; x <= range; ++x )
	{
		for( int z = -range; z <= range; ++z )
		{
			m_world.generateChunk( { x, 0, z } );
		}
	}
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
	m_renderer.setView( m_moveableView.getViewMatrix() );
	m_renderer.render( m_world );
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