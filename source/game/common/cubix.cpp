/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix.h"

namespace Game
{

Cubix::Cubix() : m_gameTime( 30 ), m_world( nullptr ) {}

void Cubix::update()
{
	m_gameTime.update();
	pollNetworkEvents();
	m_world.update( m_gameTime.getDeltaTime() );
}

void Cubix::start()
{
	while( !m_quit )
	{
		update();
	}
}

void Cubix::quit()
{
	m_quit = true;
}

} // namespace Game
