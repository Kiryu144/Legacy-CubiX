/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_NET_SERVER_H
#define CUBIX_NET_SERVER_H

#include "net_instance.h"

namespace Game
{

class NetServer : public NetInstance
{
public:
	NetServer( int port );
};

} // namespace Game

#endif
