/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_SERVER_H
#define CUBIX_CUBIX_SERVER_H

#include "game/common/cubix.h"
#include "game/server/connected_client.h"
#include "game/server/world/world_server.h"

namespace Game
{

class CubixServer : public Cubix, public Core::NetServer
{
protected:
	std::map< enet_uint32, ConnectedClient > m_connections;

	WorldServer m_world;

	void onNetworkingEvent( const ENetEvent& event ) override;
	void onPacketReceive( Core::PeerID id, std::istream& istream ) override;

private:
	void update() override;

public:
	CubixServer( int port );
};

} // namespace Game

#endif
