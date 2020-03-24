/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_server.h"

CubixServer::CubixServer( int port ) : Cubix( Game::Proxy::SERVER ), m_server( port )
{
	m_gameTime.setFPSLimit( 30 );
}
