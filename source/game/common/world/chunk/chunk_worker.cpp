/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "chunk_worker.h"

#include "game/common/world/chunk/i_world_chunk.h"
#include "game/common/world/chunk/render_world_chunk.h"
#include "game/common/worldgenerator/world_generator.h"
#include "game/common/worldgenerator/world_generator_perlin.h"

#include <string.h>

namespace Game
{

ChunkWorker::ChunkWorker( unsigned int threadAmount )
{
	for( int i = 0; i < threadAmount; ++i )
	{
		m_threads.push_back( std::thread( &ChunkWorker::worker, this ) );
	}
	Core::Logger::Log( "Starting " + std::to_string( threadAmount ) + "x chunkworker" );
}

void ChunkWorker::worker()
{
	WorldGeneratorPerlin worldGenerator;

	auto sleepTime = std::chrono::milliseconds( 50 );
	while( !m_quit )
	{
		std::this_thread::sleep_for( sleepTime );
		sleepTime = sleepTime.zero();
		std::shared_ptr< IWorldChunk > chunk;
		{
			auto guard( m_queue.lockGuard() );
			if( m_queue.empty() )
			{
				sleepTime = std::chrono::milliseconds( 100 );
				continue;
			}
			chunk = m_queue.front();
			m_queue.pop_front();
		}

		bool wasWorkDone{ false };
		if( chunk != nullptr && chunk.use_count() > 1 )
		{
			if( !chunk->isGenerated() )
			{
				worldGenerator.generateHeight( chunk );
				chunk->setGenerated();
				wasWorkDone = true;
			}

			if( !chunk->isPopulated() )
			{
				// TODO: Implement
				chunk->setPopulated();
				wasWorkDone = true;
			}

			RenderWorldChunk* renderWorldChunk = dynamic_cast< RenderWorldChunk* >( chunk.get() );
			if( renderWorldChunk && !renderWorldChunk->isMeshGenerated() )
			{
				renderWorldChunk->regenerateMesh();
				renderWorldChunk->setMeshGenerated();
				wasWorkDone = true;
			}
		}

		if( !wasWorkDone )
		{
			Core::Logger::Warn( std::string()
								+ "Chunk at [insert chunkpos] was added to chunkworker without "
								  "actually needing any work." );
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

void ChunkWorker::queue( std::shared_ptr< IWorldChunk > chunk, bool priority )
{
	auto guard( m_queue.lockGuard() );
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
	auto guard( m_queue.lockGuard() );
	return m_queue.size();
}

void ChunkWorker::checkForCrash()
{
	for( auto it = m_threads.begin(); it != m_threads.end(); )
	{
		if( !it->joinable() )
		{
			it = m_threads.erase( it );
			Core::Logger::Warn( "A chunkworker thread seems to have crashed. Worker remaining: "
								+ std::to_string( m_threads.size() ) );
		}
		else
		{
			++it;
		}
	}

	if( m_threads.size() == 0 )
	{
		Core::Logger::Warn( "There are no chunkworkers left. This is undefined behaviour. The "
							"application will be terminated!"
							+ std::string() );
		exit( -1 );
	}
}

} // namespace Game