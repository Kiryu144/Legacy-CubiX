/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PACKET_SERVER_INFORMATION_H
#define CUBIX_PACKET_SERVER_INFORMATION_H

#include "core/data/static_string.h"

#include "game/common/net/packet.h"

#include <string>

namespace Game
{

class PacketServerInformation : public Packet
{
protected:
	Core::StaticString< 32 > m_name;

public:
	PacketServerInformation( const std::string& serverName );

	const Core::StaticString< 32 >& getName() const;
};

} // namespace Game

#endif
