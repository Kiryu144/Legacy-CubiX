/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_ENTITY_H
#define CUBIX_ENTITY_H

#include "core/math/axis_aligned_bb.h"
#include "core/math/rigidbody.h"

namespace Game
{

class World;

class Entity : public Core::Rigidbody
{
protected:
	Core::AxisAlignedBB m_axisAlignedBb;

public:
	void update( World& world, float deltaTime );
};

} // namespace Game

#endif
