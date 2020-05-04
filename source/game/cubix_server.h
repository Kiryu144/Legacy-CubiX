/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_SERVER_H
#define CUBIX_CUBIX_SERVER_H

#include "core/net/net_server.h"

#include "game/cubix.h"
#include "game/player/connected_client.h"

namespace Game
{

class CubixServer : public Cubix, public Core::NetServer
{
protected:
	std::map< enet_uint32, ConnectedClient > m_connections;

	void onNetworkingEvent( const ENetEvent& event ) override;
	void onPacketReceive( Core::PeerID id, std::istream& istream ) override;

private:
	void update() override;

public:
	CubixServer( int port );
};

} // namespace Game

#endif
