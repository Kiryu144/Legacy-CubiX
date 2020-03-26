/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "server.h"

#include "core/cubix_assert.h"

namespace Game
{

Server::Server( int port )
{
	initializeEnet();
	ENetAddress address{ ENET_HOST_ANY, static_cast< enet_uint16 >( port ) };
	m_host = enet_host_create( &address, 32, 1, 0, 0 );

	cubix_assert( m_host, "Unable to initialize server" );

	Core::Logger::Log( "Net-Server created and listening on " + std::to_string( port ) );
	startWorker();
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