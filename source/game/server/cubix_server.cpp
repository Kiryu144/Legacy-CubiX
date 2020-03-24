/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_server.h"

CubixServer::CubixServer( int port ) : m_server( port )
{
	m_gameTime.setFPSLimit( 30 );
}

void CubixServer::update() {}
