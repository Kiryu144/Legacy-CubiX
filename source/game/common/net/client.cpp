/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "client.h"

#include "core/cubix_assert.h"

namespace Game
{

bool Client::connect( const std::string& name, int port )
{
	ENetAddress address;
	address.port = static_cast< enet_uint16 >( port );
	enet_address_set_host( &address, name.c_str() );

	m_peer = enet_host_connect( m_host, &address, 1, 0 );

	if( m_peer == nullptr )
	{
		Core::Logger::Log( Core::Logger::WARNING, "Invalid peer" );
		return false;
	}
	return true;
}

Client::~Client()
{
	if( m_peerConnected )
	{
		enet_peer_reset( m_peer );
	}
}

void Client::onNetworkingEvent( const ENetEvent& event )
{
	if( event.type == ENET_EVENT_TYPE_CONNECT )
	{
		Core::Logger::Log( "Connected to host" );
		m_peerConnected = true;
	}
}

} // namespace Game