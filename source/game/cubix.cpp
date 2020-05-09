/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix.h"

#include "defines.h"

namespace Game
{

Cubix::Cubix() : m_gameTime( static_cast< unsigned int >( -1 ) ) {}

void Cubix::update()
{
	m_gameTime.update();
	if( m_gameTime.getTimeSinceEpoch() - m_lastTick >= CUBIX_MS_PER_TICK )
	{
		m_lastTick = m_gameTime.getTimeSinceEpoch();
		tick();
	}
}

void Cubix::tick()
{

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
