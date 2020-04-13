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
		std::weak_ptr< WorldChunk > weakChunk;
		{
			std::lock_guard< std::mutex > guard( m_queueMutex );
			if( m_queue.empty() )
			{
				sleepTime = std::chrono::milliseconds( 100 );
				continue;
			}
			weakChunk = m_queue.front();
			m_queue.pop_front();
		}

		if( weakChunk.expired() )
		{
			return;
		}

		auto chunk = weakChunk.lock();
		std::lock_guard< std::mutex > guard( *chunk );

		switch( chunk->getChunkState() )
		{
		case WorldChunk::State::NEW:
			worldGenerator.generateHeight( *chunk );
			chunk->updateHighestBlocks();
			chunk->setChunkState( WorldChunk::State::TERRAIN_GENERATED );
			break;
		case WorldChunk::State::TERRAIN_GENERATED:
			// TODO: Implement
			chunk->setChunkState( WorldChunk::State::TERRAIN_POPULATED );
			break;
		case WorldChunk::State::TERRAIN_POPULATED:
			chunk->regenerateMesh();
			chunk->setChunkState( WorldChunk::State::DONE );
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

void ChunkWorker::queue( std::shared_ptr< WorldChunk > chunk, bool priority )
{
	std::lock_guard< std::mutex > guard( m_queueMutex );
	if( priority )
	{
		m_queue.push_front( chunk );
	}
	else
	{
		m_queue.push_back( chunk );
	}
}

size_t ChunkWorker::size()
{
	std::lock_guard< std::mutex > guard( m_queueMutex );
	return m_queue.size();
}

} // namespace Game