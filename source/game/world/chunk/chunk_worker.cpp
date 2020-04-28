/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "chunk_worker.h"

#include "game/cubix.h"
#include "game/game_performance.h"
#include "game/performance/auto_performance_monitor.h"
#include "game/world/chunk/render_world_chunk.h"
#include "game/world/chunk/world_chunk_column.h"
#include "game/world/world.h"

#include <string.h>

namespace Game
{

ChunkWorker::ChunkWorker( Cubix& game, unsigned int threadAmount ) : m_game( game )
{
	game.getPerformanceCounter().getChunkMeshCounter().resize( threadAmount );
	game.getPerformanceCounter().getTerrainGenCounter().resize( threadAmount );

	for( int i = 0; i < threadAmount; ++i )
	{
		m_threads.push_back( std::thread( &ChunkWorker::worker, this, i ) );
	}

	Core::Logger::Log( "Starting " + std::to_string( threadAmount ) + "x chunkworker" );
}

void ChunkWorker::worker( size_t threadIndex )
{
	auto& meshCounter{ m_game.getPerformanceCounter().getChunkMeshCounter()[ threadIndex ] };
	auto& terrainCounter{ m_game.getPerformanceCounter().getTerrainGenCounter()[ threadIndex ] };

	auto sleepTime = std::chrono::milliseconds( 50 );
	while( !m_quit )
	{
		std::this_thread::sleep_for( sleepTime );
		sleepTime = sleepTime.zero();
		ChunkOperation operation;
		{
			auto guard( m_queue.lockGuard() );
			if( m_queue.empty() )
			{
				sleepTime = std::chrono::milliseconds( 100 );
				continue;
			}
			operation = m_queue.front();
			m_queue.pop_front();
		}

		if( operation.column != nullptr )
		{
			if( operation.action == Action::GENERATE_TERRAIN )
			{
				AutoPerformanceMonitor m( terrainCounter );
				operation.column->getWorld().getWorldGenerator().generateHeight( operation.column );

				static const std::vector< glm::ivec2 > checks{
					glm::ivec2( 1, 0 ), glm::ivec2( -1, 0 ), glm::ivec2( 0, 1 ), glm::ivec2( 0, -1 )
				};

				for( const auto& check : checks )
				{
					const auto& column{ operation.column->getWorld().getChunkColumn( operation.column->getChunkPosition() + check ) };
					if( column != nullptr && !column->getAllNeighboursFound()
					    && column->hasAllNeighbours() )
					{
						column->setAllNeighboursFound( true );
						queue( column, ChunkWorker::POPULATE_TERRAIN );
					}
				}

				continue;
			}

			if( operation.action == Action::POPULATE_TERRAIN )
			{
				// Populate
				operation.column->getWorld().finalizeChunkColumn(
					operation.column->getChunkPosition() );

				for( auto& chunk : operation.column->getChunkColumnData() )
				{
					operation.column->getWorld().getChunkWorker().queue( chunk.second,
																		 Action::GENERATE_MESH );
				}
				continue;
			}
			continue;
		}

		if( operation.chunk != nullptr )
		{
			if( operation.action == Action::GENERATE_MESH )
			{
				RenderWorldChunk* renderWorldChunk
					= dynamic_cast< RenderWorldChunk* >( operation.chunk.get() );
				if( !renderWorldChunk )
				{
					continue;
				}
				AutoPerformanceMonitor m( meshCounter );
				renderWorldChunk->regenerateMesh();
			}
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

void ChunkWorker::queue( std::shared_ptr< WorldChunk > chunk, Action action )
{
	auto guard( m_queue.lockGuard() );
	ChunkOperation operation;
	operation.chunk	 = chunk;
	operation.action = action;
	m_queue.push_back( operation );
}

void ChunkWorker::queue( std::shared_ptr< WorldChunkColumn > column, Action action )
{
	auto guard( m_queue.lockGuard() );
	ChunkOperation operation;
	operation.column = column;
	operation.action = action;
	m_queue.push_back( operation );
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