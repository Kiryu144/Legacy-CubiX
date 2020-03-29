/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "net_client.h"
namespace Core
{

NetClient::NetClient()
{
	m_host = enet_host_create( nullptr, 1, 1, 0, 0 );

	cubix_assert( m_host, "Unable to initialize Net-Client" );
	Core::Logger::Log( "Net-Client created" );
}

bool NetClient::connect( const std::string& name, int port )
{
	ENetAddress address;
	address.port = static_cast< enet_uint16 >( port );
	enet_address_set_host( &address, name.c_str() );

	m_connectedName = name + ":" + std::to_string( port );
	m_peer			= enet_host_connect( m_host, &address, 1, 0 );

	if( m_peer == nullptr )
	{
		Core::Logger::Warn( "Invalid peer" );
		return false;
	}

	return true;
}

NetClient::~NetClient()
{
	if( m_peerConnected )
	{
		enet_peer_reset( m_peer );
	}
}

} // namespace Core