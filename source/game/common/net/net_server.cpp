/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "net_server.h"

namespace Game
{

NetServer::NetServer( int port )
{
	ENetAddress address{ ENET_HOST_ANY, static_cast< enet_uint16 >( port ) };
	m_host = enet_host_create( &address, 32, 1, 0, 0 );

	cubix_assert( m_host, "Unable to initialize server" );

	Core::Logger::Log( "Net-NetServer created and listening on " + std::to_string( port ) );
}

} // namespace Game