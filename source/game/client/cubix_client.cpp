/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_client.h"
#include "core/cubix_log.h"

CubixClient::CubixClient() : Cubix( Game::Proxy::CLIENT ), m_window( 1440, 900, "CubiX" )
{
	m_gameTime.setFPSLimit( 240 );
}

void CubixClient::update()
{
	Core::Window::Update();
	m_window.swap();

	if( m_window.shouldClose() )
	{
		quit();
	}
}
