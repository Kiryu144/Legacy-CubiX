/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix.h"

namespace Game
{

Cubix::Cubix( Proxy proxy ) : ProxySided( proxy ), m_gameTime( 30 ) {}

void Cubix::update()
{
	m_gameTime.update();
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