/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "net_instance.h"

#include <fstream>
#include <ios>
#include <sstream>

namespace Core
{

NetInstance::NetInstance()
{
	initializeEnet();
}

NetInstance::~NetInstance()
{
	enet_host_destroy( m_host );
}

void NetInstance::initializeEnet()
{
	static bool initialized{ false };
	if( !initialized )
	{
		cubix_assert( !enet_initialize(), "enet_initialize() failed" );
		initialized = true;
	}
}

void NetInstance::pollNetworkEvents()
{
	initializeEnet();
	ENetEvent event;
	while( enet_host_service( m_host, &event, 0 ) > 0 )
	{
		if( event.type == ENET_EVENT_TYPE_CONNECT )
		{
			m_peers.insert( { event.peer->connectID, event.peer } );
		}

		if( event.type == ENET_EVENT_TYPE_DISCONNECT )
		{
			m_peers.erase( event.peer->connectID );
		}

		if( event.type == ENET_EVENT_TYPE_RECEIVE )
		{
			std::stringstream ss;
			ss.write( reinterpret_cast< const char* >( event.packet->data ),
					  event.packet->dataLength );
			onPacketReceive( event.peer->connectID, ss );
		}

		if( event.type != ENET_EVENT_TYPE_NONE )
		{
			onNetworkingEvent( event );
		}
	}
}

void NetInstance::send( PeerID id, const Core::Serializeable* serializeable )
{
	if( !serializeable )
	{
		Core::Logger::Warn( "Tried to send packet with serializeable = null" );
		return;
	}

	std::stringstream out;
	serializeable->serialize( out );
	std::string data = out.str();

	if( data.empty() )
	{
		Core::Logger::Warn( "Tried to send packet with size = 0" );
		return;
	}

	auto peerPtr = getPeerForID( id );

	if( !peerPtr )
	{
		Core::Logger::Warn( "Tried to send packet to null peer" );
		return;
	}

	ENetPacket* packet
		= enet_packet_create( &data.at( 0 ), data.size(), ENET_PACKET_FLAG_RELIABLE );
	cubix_assert( packet, "enet_packet_create() returned null" );

	if( enet_peer_send( peerPtr, 0, packet ) )
	{
		Core::Logger::Warn( "Unable to send packet to peer "
							+ std::to_string( peerPtr->connectID ) );
	}
}

ENetPeer* NetInstance::getPeerForID( PeerID id ) const
{
	auto it = m_peers.find( id );
	return ( it == m_peers.end() ) ? nullptr : it->second;
}

} // namespace Core