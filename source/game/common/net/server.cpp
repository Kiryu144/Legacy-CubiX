/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "server.h"

#include "core/cubix_assert.h"

namespace Game
{

Server::Server( int port ) : NetInstance( port )
{
	Core::Logger::Register( "SERVER" );
}

void Server::onNetworkingEvent( const ENetEvent& event )
{
	switch( event.type )
	{
	case ENET_EVENT_TYPE_CONNECT:
		m_peers.insert( { event.peer->connectID, *event.peer } );
		Core::Logger::Log( "Peer connected" );
		break;
	case ENET_EVENT_TYPE_DISCONNECT:
		m_peers.erase( event.peer->connectID );
		Core::Logger::Log( "Peer disconnected" );
		break;
	default:
		break;
	}
}

} // namespace Game