/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "packet_server_information.h"

namespace Game
{

PacketServerInformation::PacketServerInformation( const std::string& playerName = "" )
	: Packet( PacketType::CLIENTBOUND_SERVER_INFORMATION ), m_name( playerName )
{
}

const Core::StaticString< 32 >& PacketServerInformation::getName() const
{
	return m_name;
}

void PacketServerInformation::serialize( std::ostream& out ) const
{
	out.write( reinterpret_cast< const char* >( &m_type ), sizeof( decltype( m_type ) ) );
	out.write( reinterpret_cast< const char* >( &m_name ), sizeof( decltype( m_name ) ) );
}

void PacketServerInformation::deserialize( std::istream& in )
{
	in.get( reinterpret_cast< char* >( &m_name ), sizeof( decltype( m_name ) ) );
}

} // namespace Game
