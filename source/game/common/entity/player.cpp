/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "player.h"

namespace Game
{

Player::Player( World& world, const std::string& name )
	: LivingEntity( world, 100.0f ), m_name( name )
{
	m_entityType = EntityType::PLAYER;
}

const std::string& Player::getName() const
{
	return m_name;
}

} // namespace Game