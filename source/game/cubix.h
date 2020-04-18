/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_H
#define CUBIX_CUBIX_H

#include "core/net/net_instance.h"
#include "core/time/game_time.h"

#include "game/packet/packet.h"
#include "game/world/world.h"

namespace Game
{

struct Cubix : public virtual Core::NetInstance
{
private:
	bool m_quit{ false };

protected:
	Core::GameTime m_gameTime;
	World m_world;

	virtual void update();

public:
	Cubix();
	void start();
	void quit();
};

} // namespace Game

#endif
