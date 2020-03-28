/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_SERVER_H
#define CUBIX_CUBIX_SERVER_H

#include "game/common/cubix.h"
#include "game/common/net/packet/packet_client_information.h"
#include "game/common/net/server.h"
#include "game/server/world/world_server.h"

namespace Game
{

class CubixServer : public Cubix, public Server
{
protected:
	std::map< enet_uint32, PacketClientInformation > m_connections;

	WorldServer m_world;

	void onPacketReceive( enet_uint32 id, const NetInstance::PacketPtr packet ) override;
	void onNetworkingEvent( const ENetEvent& event ) override;

private:
	void update() override;

public:
	CubixServer( int port );
};

} // namespace Game

#endif
