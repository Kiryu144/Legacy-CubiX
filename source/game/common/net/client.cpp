/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "client.h"

#include "core/cubix_assert.h"

namespace Game
{

Client::Client()
{
	initializeEnet();
	m_host = enet_host_create( nullptr, 1, 1, 0, 0 );

	cubix_assert( m_host, "Unable to initialize client" );
	Core::Logger::Log( "Net-Client created" );
}

bool Client::connect( const std::string& name, int port )
{
	ENetAddress address;
	address.port = static_cast< enet_uint16 >( port );
	enet_address_set_host( &address, name.c_str() );

	m_connectedName = name + ":" + std::to_string( port );
	m_peer			= enet_host_connect( m_host, &address, 1, 0 );

	if( m_peer == nullptr )
	{
		Core::Logger::Log( Core::Logger::WARNING, "Invalid peer" );
		return false;
	}

	return true;
}

void Client::onNetworkingEvent( const ENetEvent& event )
{
	if( event.type == ENET_EVENT_TYPE_CONNECT )
	{
		Core::Logger::Log( "Connected to " + m_connectedName );
		m_peerConnected = true;
	}
	else if( event.type == ENET_EVENT_TYPE_DISCONNECT )
	{
		Core::Logger::Log( "Disconnected from the server" );
		m_peerConnected = true;
	}
}

Client::~Client()
{
	if( m_peerConnected )
	{
		enet_peer_reset( m_peer );
	}
}

} // namespace Game