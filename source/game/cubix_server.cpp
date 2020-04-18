/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_server.h"

#include "game/packet/packet_client_information.h"
#include "game/packet/packet_server_information.h"

namespace Game
{

CubixServer::CubixServer( int port ) : NetServer( port )
{
	m_gameTime.setFPSLimit( 30 );
}

void CubixServer::update()
{
	Cubix::update();
	Core::NetServer::pollNetworkEvents();
	m_world.update( m_gameTime.getDeltaTime() );
}

void CubixServer::onNetworkingEvent( const ENetEvent& event )
{
	if( event.type == ENET_EVENT_TYPE_CONNECT )
	{
		PacketServerInformation packet( "Servername" );
		send( event.peer->connectID, &packet );
	}
}

void CubixServer::onPacketReceive( Core::PeerID id, std::istream& istream )
{
	PacketType type;
	istream.read( reinterpret_cast< char* >( &type ), sizeof( decltype( type ) ) );

	switch( type )
	{
	case PacketType::SERVERBOUND_PLAYER_INFORMATION:
		PacketClientInformation packetClientInformation;
		packetClientInformation.deserialize( istream );
		Core::Logger::Log( std::string( "Player " ) + packetClientInformation.getName().get()
						   + " joined the game" );
		break;
	}
}

} // namespace Game