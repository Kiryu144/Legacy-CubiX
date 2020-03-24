/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_SERVER_H
#define CUBIX_CUBIX_SERVER_H

#include "game/common/cubix.h"
#include "game/common/net/server.h"

class CubixServer : public Cubix
{
private:
	Game::Server m_server;

public:
	CubixServer( int port );
};

#endif
