/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_CLIENT_H
#define CUBIX_CUBIX_CLIENT_H

#include "core/opengl/window.h"

#include "game/common/cubix.h"
#include "game/common/net/client.h"

class CubixClient : public Cubix
{
private:
	Core::Window m_window;
	Game::Client m_netClient;

	void update() override;

public:
	CubixClient();
};

#endif
