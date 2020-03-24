/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CLIENT_H
#define CUBIX_CLIENT_H

#include "game/common/net_instance.h"

namespace Game
{

class Client : public NetInstance
{
protected:
	ENetPeer* m_peer;

public:
	Client() = default;
	virtual ~Client();

	bool connect( const std::string& name, int port );
};

} // namespace Game

#endif
