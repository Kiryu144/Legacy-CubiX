/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_server.h"

namespace Game
{

WorldServer::WorldServer() : World( Proxy::SERVER )
{
	// spawnWorker( 4 );

	int range = 10;
	for( int x = -range; x <= range; ++x )
	{
		for( int z = -range; z <= range; ++z )
		{
			// loadOrCreate( { x, 0, z } );
		}
	}
}

WorldServer::~WorldServer()
{
	m_quit = true;
	for( auto& thread : m_worker )
	{
		if( thread.joinable() )
		{
			thread.join();
		}
	}
}

void WorldServer::loadOrCreate( const glm::ivec3& position )
{
	if( m_chunks.find( position ) != m_chunks.end() )
	{
		return; // Chunk already loaded
	}

	std::shared_ptr< WorldChunk > chunk( new WorldChunk( position ) );
	m_chunks.insert( { position, chunk } );

	std::lock_guard< std::mutex > guard1( m_generationQueueMutex );
	m_generationQueue.push_back( std::weak_ptr< WorldChunk >( chunk ) );
}

void WorldServer::spawnWorker( size_t amount )
{
	for( size_t i = 0; i < amount; ++i )
	{
		m_worker.push_back( std::thread( &WorldServer::worker, this ) );
	}
}

void WorldServer::worker()
{
	Core::Logger::Register( "SERVER-CHUNK-WORKER" );
	while( !m_quit )
	{
		std::this_thread::sleep_for( std::chrono::milliseconds( 20 ) );
		std::list< std::weak_ptr< WorldChunk > >::iterator it;
		std::shared_ptr< WorldChunk > chunkWorld( nullptr );
		{
			std::lock_guard< std::mutex > guard1( m_generationQueueMutex );
			if( m_generationQueue.empty() )
			{
				continue;
			}

			it = m_generationQueue.begin();

			if( it->expired() )
			{
				m_generationQueue.erase( it );
				continue;
			}
			chunkWorld = it->lock();
			m_generationQueue.erase( it );
		}

		std::lock_guard< std::mutex > guard2( chunkWorld->getMutex() );
		chunkWorld->generateBasicNoise();
		Core::Logger::Log( "Created chunk." );
	}
	Core::Logger::UnRegister();
}

void WorldServer::update( float deltaTime )
{
	World::update( deltaTime );
}

} // namespace Game
