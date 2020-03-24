/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "client.h"

#include "core/cubix_assert.h"

namespace Game
{

bool Client::connect( const std::string& name, int port )
{
	Core::Logger::Register( "CLIENT" );
	ENetAddress address;
	enet_address_set_host( &address, name.c_str() );
	address.port = static_cast< enet_uint16 >( port );

	m_peer = *enet_host_connect( m_host, &address, 1, 0 );

	ENetEvent event;
	if( enet_host_service( m_host, &event, 5000 ) > 0 && event.type == ENET_EVENT_TYPE_CONNECT )
	{
		Core::Logger::Log( "Client connected to " + name + ":" + std::to_string( port ) + " as "
						   + std::to_string( m_peer.connectID ) );
		m_peerConnected = true;
		startWorker();
	}
	else
	{
		Core::Logger::Log( Core::Logger::WARNING,
						   "Client was unable to connect to " + name + ":"
							   + std::to_string( port ) );
		enet_peer_reset( &m_peer );
		return false;
	}
	return true;
}

Client::~Client()
{
	if( m_peerConnected )
	{
		enet_peer_reset( &m_peer );
	}
}

} // namespace Game