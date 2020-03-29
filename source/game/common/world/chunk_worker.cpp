/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "chunk_worker.h"

namespace Game
{

ChunkWorker::ChunkWorker( unsigned int threadAmount )
{
	for( int i = 0; i < threadAmount; ++i )
	{
		m_threads.push_back( std::thread( &ChunkWorker::worker, this ) );
	}
}

void ChunkWorker::worker()
{
	auto sleepTime = std::chrono::milliseconds( 20 );
	while( !m_quit )
	{
		std::this_thread::sleep_for( sleepTime );
		sleepTime = sleepTime.zero();
		Operation operation;
		{
			std::lock_guard< std::mutex > guard( m_queueMutex );
			if( m_queue.empty() )
			{
				sleepTime = std::chrono::milliseconds( 50 );
				continue;
			}
			operation = m_queue.front();
			m_queue.pop_front();
		}

		if( operation.m_worldChunk.expired() )
		{
			return;
		}

		auto chunk = operation.m_worldChunk.lock();
		std::lock_guard< std::mutex > guard( *chunk );

		switch( operation.m_operationType )
		{
		case GENERATE_TERRAIN:
			for( int x = 0; x < chunk->getSideLength(); ++x )
			{
				for( int y = 0; y < chunk->getSideLength(); ++y )
				{
					for( int z = 0; z < chunk->getSideLength(); ++z )
					{
						float fac = 255.0f / chunk->getSideLength();
						chunk->set( { x, y, z },
									{ static_cast< unsigned char >( x * fac ),
									  0,
									  static_cast< unsigned char >( z * fac ),
									  255 },
									false );
					}
				}
			}
			break;
		case GENERATE_FACES:
			chunk->updateAllFaces();
			break;
		case GENERATE_MESH:
			chunk->regenerateMesh();
		}
	}
}

ChunkWorker::~ChunkWorker()
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

void ChunkWorker::queue( std::shared_ptr< WorldChunk >& chunk,
						 ChunkWorker::OperationType operationType,
						 bool priority )
{
	std::lock_guard< std::mutex > guard( m_queueMutex );
	if( priority )
	{
		m_queue.push_front( { chunk, operationType } );
	}
	else
	{
		m_queue.push_back( { chunk, operationType } );
	}
}

} // namespace Game