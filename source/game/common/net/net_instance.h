/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_NET_INSTANCE_H
#define CUBIX_NET_INSTANCE_H

#include "defines.h"

#include "core/cubix_assert.h"
#include "core/cubix_log.h"
#include "core/data/no_copy.h"
#include "core/data/serializeable.h"

#include <atomic>
#include <thread>

#include <enet/enet.h>

namespace Game
{

class NetInstance : public Core::NoCopy
{
public:
	typedef std::unique_ptr< void, decltype( free )* > ReceivedPacketPtr;

protected:
	ENetHost* m_host;
	std::map< enet_uint32, ENetPeer* > m_peers;

	void initializeEnet();

	virtual void onNetworkingEvent( const ENetEvent& event ){};
	virtual void onPacketReceive( enet_uint32 id, const ReceivedPacketPtr packet ){};

public:
	NetInstance();
	virtual ~NetInstance();

	void pollNetworkEvents();

	ENetPeer* getPeerForID( enet_uint32 id ) const;
	void send( enet_uint32 id, const Core::Serializeable* serializeable );
};

} // namespace Game

#endif
