/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_server.h"

CubixServer::CubixServer( int port ) : Cubix( Game::Proxy::SERVER ), Game::Server( port )
{
	m_gameTime.setFPSLimit( 30 );
}

void CubixServer::onPacketReceive( enet_uint32 id, const std::unique_ptr< Game::Packet > packet )
{
	switch( packet->getType() )
	{
	case Game::PacketType::SERVERBOUND_PLAYER_INFORMATION:
	{
		Game::PacketClientInformation* clientInformation
			= static_cast< Game::PacketClientInformation* >( packet.get() );
		m_connections.insert( { id, *clientInformation } );
		Core::Logger::Log( "Player " + clientInformation->getPlayerName() + " connected" );
		break;
	}
	default:
		break;
	}
}

void CubixServer::update()
{
	Cubix::update();
	pollNetworkEvents();
}

void CubixServer::onNetworkingEvent( const ENetEvent& event )
{
	Server::onNetworkingEvent( event );
	if( event.type == ENET_EVENT_TYPE_CONNECT )
	{
		send( event.peer->connectID, Game::PacketServerInformation{ "Servername" } );
	}
}
