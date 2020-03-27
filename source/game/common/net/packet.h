/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PACKET_H
#define CUBIX_PACKET_H

namespace Game
{

enum class PacketType
{
	PACKET_PING,
	CLIENTBOUND_SERVER_INFORMATION,
	SERVERBOUND_PLAYER_INFORMATION,
	CLIENTBOUND_CREATE_ENTITY,
	CLIENTBOUND_UPDATE_ENTITY_TRANSFORMATION,
	CLIENTBOUND_FULL_CHUNK
};

class Packet
{
protected:
	PacketType m_type; // This has to be first place
public:
	Packet( PacketType type );
	const PacketType getType() const;
};

} // namespace Game

#endif // CUBIX_PACKET_H
