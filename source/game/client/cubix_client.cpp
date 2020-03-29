/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_client.h"

#include "game/common/packet/packet_client_information.h"
#include "game/common/packet/packet_server_information.h"

namespace Game
{

CubixClient::CubixClient() : Cubix( Proxy::CLIENT ), m_window( 1440, 900, "CubiX" )
{
	m_gameTime.setFPSLimit( 240 );
	connect( "127.0.0.1", 4444 );
}

void CubixClient::update()
{
	Cubix::update();
	Core::Window::Update();
	m_window.swap();
	m_world.update( m_gameTime.getDeltaTime() );

	if( m_window.shouldClose() )
	{
		quit();
	}
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

} // namespace Game