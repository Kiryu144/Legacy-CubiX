/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "packet_server_information.h"

namespace Game
{

PacketServerInformation::PacketServerInformation( const std::string& playerName )
	: Packet( PacketType::CLIENTBOUND_SERVER_INFORMATION ), m_serverName( playerName )
{
}

const std::string& PacketServerInformation::getServerName() const
{
	return m_serverName;
}

} // namespace Game
