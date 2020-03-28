/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_server.h"

namespace Game
{

CubixServer::CubixServer( int port ) : Cubix( Proxy::SERVER ), Server( port )
{
	m_gameTime.setFPSLimit( 30 );
}

void CubixServer::onPacketReceive( enet_uint32 id, const NetInstance::PacketPtr packet )
{
	switch( packet->getType() )
	{
	case PacketType::SERVERBOUND_PLAYER_INFORMATION:
	{
		PacketClientInformation* clientInformation
			= static_cast< PacketClientInformation* >( packet.get() );
		m_connections.insert( { id, *clientInformation } );
		Core::Logger::Log( std::string( "Player " ) + clientInformation->getName().get()
						   + " connected" );
		break;
	}
	default:
		break;
	}
}

void CubixServer::update()
{
	Cubix::update();
	pollNetworkEvents();
	m_world.update( m_gameTime.getDeltaTime() );
}

void CubixServer::onNetworkingEvent( const ENetEvent& event )
{
	Server::onNetworkingEvent( event );
	if( event.type == ENET_EVENT_TYPE_CONNECT )
	{
		send( event.peer->connectID, PacketServerInformation{ "Servername" } );
	}
}

} // namespace Game