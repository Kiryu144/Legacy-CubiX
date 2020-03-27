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

	if( m_window.shouldClose() )
	{
		quit();
	}
}

void CubixClient::onPacketReceive( enet_uint32 id, const std::unique_ptr< Packet > packet )
{
	switch( packet->getType() )
	{
	case PacketType::CLIENTBOUND_SERVER_INFORMATION:
		m_serverInfo = *static_cast< PacketServerInformation* >( packet.get() );
		Core::Logger::Log( "Servername is '" + m_serverInfo.getServerName() + "'" );
		send( id, PacketClientInformation( "Kiryu144" ) );
		break;
	default:
		break;
	}
}

} // namespace Game