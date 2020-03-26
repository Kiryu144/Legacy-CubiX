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
	std::string m_name;

public:
	Player( World& world, const std::string& name );

	const std::string& getName() const;
};

} // namespace Game

#endif
