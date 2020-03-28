/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_NET_INSTANCE_H
#define CUBIX_NET_INSTANCE_H

#include "defines.h"

#include "core/cubix_assert.h"
#include "core/cubix_log.h"

#include "game/common/net/packet.h"
#include "game/common/net/packet/packet_server_information.h"

#include <atomic>
#include <thread>

#include <enet/enet.h>

namespace Game
{

class NetInstance
{
public:
	typedef std::unique_ptr< Packet, decltype( free )* > PacketPtr;

protected:
	ENetHost* m_host;
	std::map< enet_uint32, ENetPeer* > m_peers;

	void initializeEnet();

	virtual void onNetworkingEvent( const ENetEvent& event ){};
	virtual void onPacketReceive( enet_uint32 id, const PacketPtr packet ){};

public:
	NetInstance()							= default;
	NetInstance( const NetInstance& other ) = delete;
	virtual ~NetInstance();

	void pollNetworkEvents();

	template< typename T >
	void send( enet_uint32 id, const T& packet )
	{
		cubix_assert( sizeof( T ) >= sizeof( Packet ), "Invalid packet size" );
		auto it = m_peers.find( id );
		cubix_assert( it != m_peers.end(), "Unknown ID" );
		ENetPacket* p = enet_packet_create( &packet, sizeof( T ), ENET_PACKET_FLAG_RELIABLE );
		enet_peer_send( it->second, 0, p );
	}
};

} // namespace Game

#endif
