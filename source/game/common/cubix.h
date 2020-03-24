/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_H
#define CUBIX_CUBIX_H

#include "core/math/game_time.h"
#include "game/common/world/world.h"

struct Cubix
{
private:
	bool m_quit{ false };

	virtual void update();

protected:
	Core::GameTime m_gameTime;
	// Game::World m_world;

public:
	Cubix();

	void start();
	void quit();
};

#endif
