/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "entity.h"

namespace Game
{

Entity::Entity( World& world ) : m_world( &world ), m_entityType( EntityType::ENTITY ) {}

const EntityType Entity::getEntityType() const
{
	return m_entityType;
}

bool Entity::isRemove() const
{
	return m_remove;
}

void Entity::remove()
{
	m_remove = true;
}

} // namespace Game
