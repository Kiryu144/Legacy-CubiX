/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PACKET_CLIENT_INFORMATION_H
#define CUBIX_PACKET_CLIENT_INFORMATION_H

#include "core/data/static_string.h"

#include "game/common/net/packet.h"

#include <array>
#include <string>

namespace Game
{

class PacketClientInformation : public Packet
{
protected:
	Core::StaticString< 32 > m_name;

public:
	PacketClientInformation( const std::string& playerName );

	const Core::StaticString< 32 >& getName() const;
};

} // namespace Game

#endif
