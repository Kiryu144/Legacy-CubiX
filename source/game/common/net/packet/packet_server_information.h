/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PACKET_SERVER_INFORMATION_H
#define CUBIX_PACKET_SERVER_INFORMATION_H

#include "game/common/net/packet.h"

#include <string>

namespace Game
{

class PacketServerInformation : public Packet
{
protected:
	std::string m_serverName;

public:
	PacketServerInformation( const std::string& serverName );

	const std::string& getServerName() const;
};

} // namespace Game

#endif
