/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PACKET_CLIENT_INFORMATION_H
#define CUBIX_PACKET_CLIENT_INFORMATION_H

#include "packet.h"

#include "core/data/static_string.h"

#include <string>

namespace Game
{

class PacketClientInformation : public Packet
{
protected:
	Core::StaticString< 32 > m_name;

public:
	PacketClientInformation( const std::string& serverName = "" );

	const Core::StaticString< 32 >& getName() const;

	void serialize( std::ostream& out ) const override;
	void deserialize( std::istream& in ) override;
};

} // namespace Game

#endif
