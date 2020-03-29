/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_CLIENT_H
#define CUBIX_CUBIX_CLIENT_H

#include "core/net/net_client.h"
#include "core/opengl/window.h"

#include "game/client/world/world_client.h"
#include "game/common/cubix.h"

namespace Game
{

class CubixClient : public Cubix, public Core::NetClient
{
private:
	Core::Window m_window;
	WorldClient m_world;

	void update() override;

protected:
	void onPacketReceive( Core::PeerID id, std::istream& istream ) override;

public:
	CubixClient();
};

} // namespace Game

#endif
