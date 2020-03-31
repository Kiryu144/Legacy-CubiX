/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PACKET_H
#define CUBIX_PACKET_H

#include "core/data/serializeable.h"

namespace Game
{

enum class PacketType
{
	UNINITIALIZED = 0, // Has to be zero
	PACKET_PING,
	CLIENTBOUND_SERVER_INFORMATION,
	SERVERBOUND_PLAYER_INFORMATION
};

class Packet : public Core::Serializeable
{
protected:
	PacketType m_type; // This has to be first place
public:
	Packet( PacketType type );
	const PacketType getType() const;
};

} // namespace Game

#endif // CUBIX_PACKET_H
