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

void PacketClientInformation::serialize( std::ostream& out ) const
{
	out.write( reinterpret_cast< const char* >( &m_type ), sizeof( decltype( m_type ) ) );
	out.write( reinterpret_cast< const char* >( &m_name ), sizeof( decltype( m_name ) ) );
}

void PacketClientInformation::deserialize( std::istream& in )
{
	in.get( reinterpret_cast< char* >( &m_name ), sizeof( decltype( m_name ) ) );
}

} // namespace Game
