/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world.h"

namespace Game
{

World::World( const Proxy& proxy ) : ProxySided( proxy ) {}

void World::update( float deltaTime )
{
	for( auto it = m_entities.begin(); it != m_entities.end(); ++it )
	{
		Entity* entity = it->get();

		if( entity->isRemove() )
		{
			it = m_entities.erase( it );
			continue;
		}

		entity->update( deltaTime );
	}
}

void World::spawn( Entity* entity )
{
	m_entities.emplace_back( entity );
}

} // namespace Game