/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PLAYER_H
#define CUBIX_PLAYER_H

#include "game/common/entity/living_entity.h"

namespace Game
{

class Player : public LivingEntity
{
protected:
	unsigned int m_id;

public:
	Player( World& world, unsigned int id );

	unsigned int getId() const;
};

} // namespace Game

#endif
