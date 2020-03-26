/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PACKET_CLIENT_INFORMATION_H
#define CUBIX_PACKET_CLIENT_INFORMATION_H

#include "game/common/net/packet.h"

#include <string>

namespace Game
{

class PacketClientInformation : public Packet
{
protected:
	std::string m_playerName;

public:
	PacketClientInformation( const std::string& playerName );

	const std::string& getPlayerName() const;
};

} // namespace Game

#endif
