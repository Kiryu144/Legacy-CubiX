/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "connected_client.h"

namespace Game
{

ConnectedClient::ConnectedClient( enet_uint32 id, const std::string& name )
	: m_id( id ), m_name( name )
{
}

const std::string& ConnectedClient::getName() const
{
	return m_name;
}

enet_uint32 ConnectedClient::getId() const
{
	return m_id;
}

} // namespace Game