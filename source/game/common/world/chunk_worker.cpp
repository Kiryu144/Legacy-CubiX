/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "chunk_worker.h"

#include "game/common/world/world_chunk.h"
#include "game/common/worldgenerator/world_generator.h"
#include "game/common/worldgenerator/world_generator_perlin.h"

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
	WorldGeneratorPerlin worldGenerator;
	auto sleepTime = std::chrono::milliseconds( 50 );
	while( !m_quit )
	{
		std::this_thread::sleep_for( sleepTime );
		sleepTime = sleepTime.zero();
		Operation operation;
		{
			std::lock_guard< std::mutex > guard( m_queueMutex );
			if( m_queue.empty() )
			{
				sleepTime = std::chrono::milliseconds( 100 );
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
			worldGenerator.generateHeight( *chunk );
			chunk->setTerrainGenerated( true );
			break;
		case GENERATE_MESH:
			chunk->regenerateMesh();
			if( chunk->getVoxelCount() == 0 )
			{
				chunk->getWorld().deleteChunk( chunk->getChunkPosition() );
			}
			else
			{
				chunk->setRender( true );
			}
			break;
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

void ChunkWorker::queue( std::shared_ptr< WorldChunk > chunk,
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

size_t ChunkWorker::size()
{
	std::lock_guard< std::mutex > guard( m_queueMutex );
	return m_queue.size();
}

} // namespace Game