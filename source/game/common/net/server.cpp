/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "server.h"

#include "core/cubix_assert.h"

namespace Game
{

Server::Server( int port ) : NetInstance( port ) {}

void Server::onNetworkingEvent( const ENetEvent& event )
{
	switch( event.type )
	{
	case ENET_EVENT_TYPE_CONNECT:
		m_peers.insert( { event.peer->connectID, *event.peer } );
		break;
	case ENET_EVENT_TYPE_DISCONNECT:
		m_peers.erase( event.peer->connectID );
		break;
	}
}

} // namespace Game