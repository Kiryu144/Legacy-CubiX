/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_H
#define CUBIX_CUBIX_H

#include "core/math/game_time.h"

#include "game/common/world/world.h"

struct Cubix : public Game::ProxySided
{
private:
	bool m_quit{ false };

protected:
	Core::GameTime m_gameTime;
	Game::World m_world;

	virtual void update();

public:
	Cubix( Game::Proxy proxy );

	void start();
	void quit();
};

#endif
