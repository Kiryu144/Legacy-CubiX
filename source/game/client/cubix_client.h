/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_CLIENT_H
#define CUBIX_CUBIX_CLIENT_H

#include "core/opengl/window.h"

#include "game/client/world/world_client.h"
#include "game/common/cubix.h"
#include "game/common/net/client.h"
#include "game/common/net/packet/packet_server_information.h"

namespace Game
{

class CubixClient : public Cubix, public Client
{
private:
	Core::Window m_window;
	PacketServerInformation m_serverInfo{ "" };

	WorldClient m_world;

	void update() override;

protected:
	void onPacketReceive( enet_uint32 id, const NetInstance::PacketPtr packet ) override;

public:
	CubixClient();
};

} // namespace Game

#endif
