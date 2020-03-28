/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "net_instance.h"

#include "core/cubix_assert.h"

#include <memory>

namespace Game
{

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

		if( event.type == ENET_EVENT_TYPE_RECEIVE
			&& event.packet->dataLength >= sizeof( PacketType ) )
		{
			PacketType type = *reinterpret_cast< PacketType* >( event.packet->data );
			cubix_assert( type != PacketType::UNINITIALIZED, "Received packet is not initialized" );
			cubix_assert( event.packet->dataLength >= sizeof( Packet ),
						  "Invalid packet size received" );
			PacketPtr packet( static_cast< Packet* >( malloc( event.packet->dataLength ) ), free );
			memcpy( packet.get(), event.packet->data, event.packet->dataLength );
			onPacketReceive( event.peer->connectID, std::move( packet ) );
			enet_packet_destroy( event.packet );
		}

		if( event.type != ENET_EVENT_TYPE_NONE )
		{
			onNetworkingEvent( event );
		}
	}
}

} // namespace Game