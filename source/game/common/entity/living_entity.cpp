/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "living_entity.h"

#include "game/common/world/world.h"

namespace Game
{

LivingEntity::LivingEntity( Game::World& world, float maxHealth )
	: Entity( world ), m_health( maxHealth ), m_maxHealth( maxHealth )
{
	m_entityType = EntityType::LIVING_ENTITY;
}

float LivingEntity::getMaxHealth() const
{
	return m_maxHealth;
}

float LivingEntity::getHealth() const
{
	return m_health;
}

void LivingEntity::setHealth( float health )
{
	m_health = health;
}

bool LivingEntity::isAlive() const
{
	return m_health < 0.001f;
}

void LivingEntity::update( float deltaTime )
{
	Entity::update( deltaTime );
	if( m_world->getProxy() == Proxy::SERVER )
	{
		getPosition() += m_velocity * glm::vec3( deltaTime );
	}
}

} // namespace Game
