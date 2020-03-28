/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "net_instance.h"

namespace Game
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
			ReceivedPacketPtr dataPtr( malloc( event.packet->dataLength ), free );
			memcpy( dataPtr.get(), event.packet->data, event.packet->dataLength );
			onPacketReceive( event.peer->connectID, std::move( dataPtr ) );
		}

		if( event.type != ENET_EVENT_TYPE_NONE )
		{
			onNetworkingEvent( event );
		}
	}
}

void NetInstance::send( enet_uint32 id, const Core::Serializeable* serializeable )
{
	if( !serializeable )
	{
		Core::Logger::Warn( "Tried to send packet with serializeable = null" );
		return;
	}

	size_t serializedDataSize = 0;
	auto serializedDataPtr	  = serializeable->serialize( serializedDataSize );

	if( !serializedDataSize )
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

	ENetPacket* packet = enet_packet_create(
		serializedDataPtr.get(), serializedDataSize, ENET_PACKET_FLAG_RELIABLE );
	cubix_assert( packet, "enet_packet_create() returned null" );

	if( !enet_peer_send( peerPtr, 0, packet ) )
	{
		Core::Logger::Warn( "Unable to send packet to peer "
							+ std::to_string( peerPtr->connectID ) );
	}
}

ENetPeer* NetInstance::getPeerForID( enet_uint32 id ) const
{
	auto it = m_peers.find( id );
	return ( it == m_peers.end() ) ? nullptr : it->second;
}

} // namespace Game