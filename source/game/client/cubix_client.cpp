/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_client.h"

CubixClient::CubixClient() : m_window( 1440, 900, "CubiX" )
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
