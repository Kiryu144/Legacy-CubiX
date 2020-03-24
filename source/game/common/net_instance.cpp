/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "net_instance.h"

#include "core/cubix_assert.h"

namespace Game
{

NetInstance::NetInstance( int port )
{
	initializeEnet();
	ENetAddress address{ ENET_HOST_ANY, static_cast< enet_uint16 >( port ) };
	m_host = enet_host_create( &address, 32, 1, 0, 0 );

	cubix_assert( m_host, "Unable to initialize server" );
	Core::Logger::Log( "Server created and listening on " + std::to_string( port ) );

	startWorker();
}

NetInstance::NetInstance()
{
	initializeEnet();
	m_host = enet_host_create( nullptr, 1, 1, 0, 0 );

	cubix_assert( m_host, "Unable to initialize client" );

	Core::Logger::Log( "Client created" );
	m_worker = std::thread( &NetInstance::worker, this );
}

NetInstance::~NetInstance()
{
	m_quitWorker = true;
	if( m_worker.joinable() )
	{
		m_worker.join();
	}
	enet_host_destroy( m_host );
}

void NetInstance::initializeEnet()
{
	cubix_assert( !enet_initialize(), "enet_initialize() failed" );
}

void NetInstance::worker()
{
	ENetEvent event;
	while( !m_quitWorker && enet_host_service( m_host, &event, 10 ) > 0 )
	{
		if( event.type != ENET_EVENT_TYPE_NONE )
		{
			onNetworkingEvent( event );
		}
	}
}

void NetInstance::startWorker()
{
	if( !m_worker.joinable() )
	{
		m_worker = std::thread( &NetInstance::worker, this );
	}
}

} // namespace Game