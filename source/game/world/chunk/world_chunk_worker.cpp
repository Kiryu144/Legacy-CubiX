/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_worker.h"

#include "core/io/window.h"
#include "core/time/auto_stop_watch.h"

#include "game/world/chunk/world_chunk.h"
#include "game/world/chunk/world_chunk_mesh.h"

namespace Game
{

WorldChunkWorker::WorldChunkWorker( size_t threads )
{
	for( int i = 0; i < threads; ++i )
	{
		m_threads.push_back( std::thread( &WorldChunkWorker::worker, this, i ) );
	}
}

WorldChunkWorker::~WorldChunkWorker()
{
	m_quit = true;
	for( auto& thread : m_threads )
	{
		if( thread.joinable() )
		{
			thread.join();
		}
	}
}

void WorldChunkWorker::worker( int index )
{
	while( !m_quit )
	{
		Operation operation{ Action::POPULATE, nullptr };
		{
			std::lock_guard< decltype( m_queueMutex ) > guard( m_queueMutex );
			if( !m_queue.empty() )
			{
				operation = m_queue.front();
				m_queue.pop_front();
			}
		}

		if( !operation.chunk )
		{
			std::this_thread::sleep_for( std::chrono::milliseconds( 20 ) );
			continue;
		}

		switch( operation.action )
		{
		case GENERATE:
		{
			for( int x = 0; x < CUBIX_CHUNK_SIZE; ++x )
			{
				for( int z = 0; z < CUBIX_CHUNK_SIZE; ++z )
				{
					for( int y = 0; y < ( ( sin( x / 20.0f ) + 1.0f ) * 5.0f ); ++y )
					{
						operation.chunk->setVoxel( { x, y, z }, Voxel{ 0, 128, 0, 255 } );
					}
				}
			}
			operation.chunk->setGenerated( true );
			break;
		}
		case POPULATE:
		{
			operation.chunk->setPopulated( true );
			break;
		}
		case MESH:
		{
			operation.chunk->getWorldChunkMesh().reset( new WorldChunkMesh(
				operation.chunk->getWorld(), operation.chunk->getChunkPosition() ) );
			operation.chunk->getWorldChunkMesh()->generate();
			break;
		}
		}

		operation.chunk->setWorkedOn( false );
	}
}

void WorldChunkWorker::queue( std::shared_ptr< WorldChunk >& chunk,
							  WorldChunkWorker::Action action )
{
	cubix_assert( !chunk->isWorkedOn(), "Chunk is already being worked on" );
	std::lock_guard< decltype( m_queueMutex ) > guard( m_queueMutex );
	chunk->setWorkedOn( true );
	m_queue.push_back( { action, chunk } );
}

} // namespace Game