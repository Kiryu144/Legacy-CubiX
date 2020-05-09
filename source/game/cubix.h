/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_H
#define CUBIX_CUBIX_H

#include "core/time/game_time.h"

namespace Game
{

struct Cubix
{
private:
	bool m_quit{ false };

protected:
	Core::GameTime m_gameTime;
	double m_lastTick{ 0 };

	virtual void update();
	virtual void tick();

public:
	Cubix();
	void start();
	void quit();
};

} // namespace Game

#endif
