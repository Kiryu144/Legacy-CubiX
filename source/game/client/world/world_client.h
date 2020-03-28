/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CLIENT_H
#define CUBIX_WORLD_CLIENT_H

#include "game/common/world/world.h"

namespace Game
{

class WorldClient : public World
{

protected:
public:
	WorldClient();
	void draw( Core::ShaderProgram& shader, const glm::mat4& view, const glm::mat4& projection );
};

} // namespace Game

#endif
