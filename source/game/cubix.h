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

	virtual void update();

public:
	Cubix();
	void start();
	void quit();
};

} // namespace Game

#endif
