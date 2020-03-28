/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_client.h"

#include "game/common/net/packet/packet_client_information.h"

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
	pollNetworkEvents();
	m_window.swap();
	m_world.update( m_gameTime.getDeltaTime() );

	if( m_window.shouldClose() )
	{
		quit();
	}
}

void CubixClient::onPacketReceive( enet_uint32 id, const NetInstance::PacketPtr packet )
{
	switch( packet->getType() )
	{
	case PacketType::CLIENTBOUND_SERVER_INFORMATION:
	{
		m_serverInfo = *static_cast< PacketServerInformation* >( packet.get() );
		Core::Logger::Log( std::string( "Servername is '" ) + m_serverInfo.getName().get() + "'" );
		PacketClientInformation test( "Kiryu144" );
		send( id, test );
		break;
	}
	default:
		break;
	}
}

} // namespace Game