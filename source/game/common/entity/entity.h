/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_ENTITY_H
#define CUBIX_ENTITY_H

#include "core/opengl/shader_program.h"
#include "core/math/transform.h"
#include "game/proxy.h"
#include "game/common/entity/entitytype.h"

namespace Game
{

class World;

class Entity : public Core::Transform
{
protected:
	bool m_remove{ false };
	EntityType m_entityType;
	Game::World* m_world;

public:
	Entity( World& world );
	virtual ~Entity() = default;

	virtual void update( float deltaTime ){};

	const EntityType getEntityType() const;
	bool isRemove() const;
	void remove();
};

} // namespace Game

#endif
