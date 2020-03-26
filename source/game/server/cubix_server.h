/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_SERVER_H
#define CUBIX_CUBIX_SERVER_H

#include "game/common/cubix.h"
#include "game/common/net/server.h"

class CubixServer : public Cubix, public Game::Server
{
private:
	void onPacketReceive( PacketType type, Packet data ) override;

public:
	CubixServer( int port );
};

#endif
