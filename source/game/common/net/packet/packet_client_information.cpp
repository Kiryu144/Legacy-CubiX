/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "packet_client_information.h"

namespace Game
{

PacketClientInformation::PacketClientInformation( const std::string& playerName )
	: Packet( PacketType::SERVERBOUND_PLAYER_INFORMATION ), m_name( playerName )
{
}

const Core::StaticString< 32 >& PacketClientInformation::getName() const
{
	return m_name;
}

} // namespace Game
