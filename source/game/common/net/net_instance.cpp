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
	m_quitWorker = true;
	if( m_worker.joinable() )
	{
		m_worker.join();
	}
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

void NetInstance::worker()
{
	initializeEnet();
	ENetEvent event;
	while( !m_quitWorker )
	{
		while( !m_quitWorker && enet_host_service( m_host, &event, 0 ) >= 0 )
		{
			if( event.type != ENET_EVENT_TYPE_NONE )
			{
				onNetworkingEvent( event );
			}

			if( event.type == ENET_EVENT_TYPE_RECEIVE
				&& event.packet->dataLength >= sizeof( PacketType ) )
			{
				PacketType type = *reinterpret_cast< PacketType* >(
					event.packet->data + event.packet->dataLength - sizeof( PacketType ) );
				Packet packet( event.packet, enet_packet_destroy );
				onPacketReceive( type, std::move( packet ) );
			}
		}
	}
}

void NetInstance::startWorker()
{
	if( !m_worker.joinable() )
	{
		m_worker = std::thread( &NetInstance::worker, this );
		Core::Logger::Register( "Net-" + Core::Logger::GetID(), m_worker.get_id() );
	}
}

void NetInstance::broadcast( PacketType type, size_t size, void* data )
{
	ENetPacket* packet = enet_packet_create( data, size, ENET_PACKET_FLAG_RELIABLE );
	enet_packet_resize( packet, size + sizeof( type ) );
	memcpy( static_cast< char* >( data ) + size, &data, sizeof( type ) );
	enet_host_broadcast( m_host, 0, packet );
}

} // namespace Game