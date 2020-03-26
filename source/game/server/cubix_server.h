/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_SERVER_H
#define CUBIX_CUBIX_SERVER_H

#include "game/common/cubix.h"
#include "game/common/net/server.h"

#include "game/common/net/packet/packet_client_information.h"

class CubixServer : public Cubix, public Game::Server
{
protected:
	std::map< enet_uint32, Game::PacketClientInformation > m_connections;

	void onPacketReceive( enet_uint32 id, const std::unique_ptr< Game::Packet > packet ) override;
	void onNetworkingEvent( const ENetEvent& event ) override;

private:
	void update() override;

public:
	CubixServer( int port );
};

#endif
