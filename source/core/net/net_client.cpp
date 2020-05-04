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

bool NetClient::connect( const std::string& name )
{
	std::string host{ name.substr( 0, name.find_first_of( ':' ) ) };
	int port = name.size() > host.size() + 1 ?
		std::stoi( name.substr( host.size() + 1, name.find_first_not_of( "0123456789" ) + 1 ) ) :
		4444;

	m_connectedName = host + ":" + std::to_string( port );
	Core::Logger::Log( "Trying to connect to " + m_connectedName );

	ENetAddress address;
	address.port = static_cast< enet_uint16 >( port );
	enet_address_set_host( &address, host.c_str() );
	m_peer = enet_host_connect( m_host, &address, 1, 0 );

	return true;
}

void NetClient::disconnect()
{
	if( m_peerConnected )
	{
		enet_peer_reset( m_peer );
		Core::Logger::Log( "Disconnected from " + m_connectedName );
		m_peerConnected = false;
		m_connectedName = "";
		m_peer			= nullptr;
	}
}

NetClient::~NetClient()
{
	disconnect();
}

void NetClient::onNetworkingEvent( const ENetEvent& event )
{
	NetInstance::onNetworkingEvent( event );
	if(event.type == ENET_EVENT_TYPE_CONNECT)
	{
		Core::Logger::Log( "Connected to " + m_connectedName );
		m_peerConnected = true;
	}
}

} // namespace Core