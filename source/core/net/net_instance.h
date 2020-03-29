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

namespace Core
{

typedef enet_uint32 PeerID;

class NetInstance : public Core::NoCopy
{
protected:
	ENetHost* m_host;
	std::map< PeerID, ENetPeer* > m_peers;

	void initializeEnet();

	virtual void onNetworkingEvent( const ENetEvent& event ){};
	virtual void onPacketReceive( PeerID id, std::istream& istream ){};

public:
	NetInstance();
	virtual ~NetInstance();

	void pollNetworkEvents();

	ENetPeer* getPeerForID( PeerID id ) const;
	void send( PeerID id, const Core::Serializeable* serializeable );
};

} // namespace Core

#endif
