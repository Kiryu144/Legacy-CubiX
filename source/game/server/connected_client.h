/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CONNECTED_CLIENT_H
#define CUBIX_CONNECTED_CLIENT_H

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

public:
	ConnectedClient( enet_uint32 id, const std::string& name );

	const std::string& getName() const;
	enet_uint32 getId() const;
};

} // namespace Game

#endif
