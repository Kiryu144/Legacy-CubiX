#include "packet.h"
/*
 * Copyright (c) 2020 David Klostermann.
 */

namespace Game
{

Packet::Packet( PacketType type ) : m_type( type ) {}

const PacketType Packet::getType() const
{
	return m_type;
}

} // namespace Game