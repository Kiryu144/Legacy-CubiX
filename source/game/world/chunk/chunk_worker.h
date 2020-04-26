/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CHUNK_WORKER_H
#define CUBIX_CHUNK_WORKER_H

#include "core/logic/lockable.h"
#include "core/logic/no_copy.h"

#include <atomic>
#include <list>
#include <mutex>
#include <thread>

namespace Game
{

class WorldChunk;
class WorldChunkColumn;

class ChunkWorker : Core::NoCopy
{
public:
	enum Action
	{
		GENERATE_TERRAIN,
		POPULATE_TERRAIN,
		GENERATE_MESH
	};

protected:
	struct ChunkOperation
	{
		Action action;
		std::shared_ptr< WorldChunk > chunk{ nullptr };
		std::shared_ptr< WorldChunkColumn > column{ nullptr };
	};

protected:
	std::atomic_bool m_quit{ false };
	void worker();

	std::list< std::thread > m_threads;
	Core::Lockable< std::list< ChunkOperation > > m_queue;

public:
	ChunkWorker( unsigned int threadAmount );
	~ChunkWorker();

	void queue( std::shared_ptr< WorldChunk > chunk, Action action );
	void queue( std::shared_ptr< WorldChunkColumn > column, Action action );

	void checkForCrash();

	size_t size();
};

} // namespace Game

#endif
