/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_H
#define CUBIX_CUBIX_H

#include "core/math/game_time.h"
#include "core/net/net_instance.h"

#include "game/common/packet/packet.h"
#include "game/common/world/world.h"

namespace Game
{

struct Cubix : public ProxySided, public virtual Core::NetInstance
{
private:
	bool m_quit{ false };

protected:
	Core::GameTime m_gameTime;

	virtual void update();

public:
	Cubix( Proxy proxy );

	void start();
	void quit();
};

} // namespace Game

#endif
