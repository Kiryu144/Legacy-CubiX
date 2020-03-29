/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CONNECTED_CLIENT_H
#define CUBIX_CONNECTED_CLIENT_H

#include "game/common/entity/player.h"

#include <memory>
#include <string>

#include <enet/enet.h>

namespace Game
{

class ConnectedClient
{
private:
	enet_uint32 m_id;
	std::string m_name;

	Player* m_entity;

public:
	ConnectedClient( enet_uint32 id, const std::string& name );

	const std::string& getName() const;
	enet_uint32 getId() const;

	Player* getEntity();
	void setEntity( Player* entity );
};

} // namespace Game

#endif
