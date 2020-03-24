/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_SERVER_H
#define CUBIX_SERVER_H

#include "net_instance.h"

#include <map>

namespace Game
{

class Server : public NetInstance
{
protected:
	std::map< enet_uint32, ENetPeer > m_peers;

	void onNetworkingEvent( const ENetEvent& event ) override;

public:
	Server( int port );
};

} // namespace Game

#endif
