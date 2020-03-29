/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "player.h"

namespace Game
{

Player::Player( World& world, unsigned int id ) : LivingEntity( world, 100.0f ), m_id( id )
{
	m_entityType = EntityType::PLAYER;
}

unsigned int Player::getId() const
{
	return m_id;
}

} // namespace Game