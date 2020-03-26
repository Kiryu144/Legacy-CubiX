/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "packet_client_information.h"

namespace Game
{

PacketClientInformation::PacketClientInformation( const std::string& playerName )
	: Packet( PacketType::SERVERBOUND_PLAYER_INFORMATION ), m_playerName( playerName )
{
}

const std::string& PacketClientInformation::getPlayerName() const
{
	return m_playerName;
}

} // namespace Game
