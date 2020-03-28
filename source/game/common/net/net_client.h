/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_NET_CLIENT_H
#define CUBIX_NET_CLIENT_H

#include "net_instance.h"

namespace Game
{

class NetClient : public NetInstance
{
protected:
	ENetPeer* m_peer;
	bool m_peerConnected{ false };
	std::string m_connectedName;

public:
	NetClient();
	virtual ~NetClient();

	bool connect( const std::string& name, int port );
};

} // namespace Game

#endif
