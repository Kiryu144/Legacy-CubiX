/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "packet_server_information.h"

namespace Game
{

PacketServerInformation::PacketServerInformation( const std::string& playerName )
	: Packet( PacketType::CLIENTBOUND_SERVER_INFORMATION ), m_name( playerName )
{
}

const Core::StaticString< 32 >& PacketServerInformation::getName() const
{
	return m_name;
}

} // namespace Game
