/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CHUNK_WORKER_H
#define CUBIX_CHUNK_WORKER_H

#include "core/logic/no_copy.h"

#include <atomic>
#include <list>
#include <mutex>
#include <thread>

namespace Game
{

class WorldChunk;

class ChunkWorker : Core::NoCopy
{
private:
	std::atomic_bool m_quit{ false };
	void worker();

protected:
	std::list< std::thread > m_threads;

	std::mutex m_queueMutex;
	std::list< std::weak_ptr< WorldChunk > > m_queue;

public:
	ChunkWorker( unsigned int threadAmount );
	~ChunkWorker();

	void queue( std::shared_ptr< WorldChunk > chunk,
				bool priority = false );

	size_t size();
};

} // namespace Game

#endif
