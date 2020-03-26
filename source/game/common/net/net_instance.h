/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_NET_INSTANCE_H
#define CUBIX_NET_INSTANCE_H

#include "defines.h"

#include <enet/enet.h>
#include <thread>
#include <atomic>

#include "game/common/net/packet_type.h"

namespace Game
{

class NetInstance
{
protected:
	typedef std::unique_ptr< ENetPacket, decltype( &enet_packet_destroy ) > Packet;

	ENetHost* m_host;
	std::thread m_worker;
	std::atomic_bool m_quitWorker{ false };

	void initializeEnet();
	void worker();
	void startWorker();

	virtual void onNetworkingEvent( const ENetEvent& event ){};
	virtual void onPacketReceive( PacketType type, Packet data ){};

public:
	NetInstance()							= default;
	NetInstance( const NetInstance& other ) = delete;
	virtual ~NetInstance();

	void broadcast( PacketType type, size_t size, void* data );
};

} // namespace Game

#endif
