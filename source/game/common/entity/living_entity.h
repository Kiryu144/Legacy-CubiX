/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_LIVING_ENTITY_H
#define CUBIX_LIVING_ENTITY_H

#include "game/common/entity/entity.h"

namespace Game
{

class LivingEntity : public Entity
{
protected:
	glm::vec3 m_velocity;

	float m_maxHealth;
	float m_health;

public:
	LivingEntity( World& world, float maxHealth );

	float getMaxHealth() const;
	float getHealth() const;
	void setHealth( float health );

	bool isAlive() const;

	void update( float deltaTime ) override;
};

} // namespace Game

#endif
