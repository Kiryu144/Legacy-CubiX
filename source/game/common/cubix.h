/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_H
#define CUBIX_CUBIX_H

#include "core/logic/game_time.h"
#include "core/net/net_instance.h"

#include "game/common/packet/packet.h"
#include "game/common/world/world.h"

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
