/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_NET_SERVER_H
#define CUBIX_NET_SERVER_H

#include "net_instance.h"

namespace Core
{

class NetServer : public virtual NetInstance
{
public:
	NetServer( int port );
};

} // namespace Core

#endif
