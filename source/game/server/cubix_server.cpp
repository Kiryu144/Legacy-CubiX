/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_server.h"

CubixServer::CubixServer( int port ) : Cubix( Game::Proxy::SERVER ), Game::Server( port )
{
	m_gameTime.setFPSLimit( 30 );
}

void CubixServer::onPacketReceive( PacketType type, Game::NetInstance::Packet data ) {}
