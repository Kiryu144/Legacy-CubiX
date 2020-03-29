/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PACKET_SERVER_INFORMATION_H
#define CUBIX_PACKET_SERVER_INFORMATION_H

#include "packet.h"

#include "core/data/static_string.h"

#include <string>

namespace Game
{

class PacketServerInformation : public Packet
{
protected:
	Core::StaticString< 32 > m_name;

public:
	PacketServerInformation( const std::string& serverName );

	const Core::StaticString< 32 >& getName() const;

	void serialize( std::ostream& out ) const override;
	void deserialize( std::istream& in ) override;
};

} // namespace Game

#endif
