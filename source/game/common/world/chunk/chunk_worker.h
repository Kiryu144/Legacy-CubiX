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

class IWorldChunk;

class ChunkWorker : Core::NoCopy
{
private:
	std::atomic_bool m_quit{ false };
	void worker();

protected:
	std::list< std::thread > m_threads;
	Core::Lockable< std::list< std::shared_ptr< IWorldChunk > > > m_queue;

public:
	ChunkWorker( unsigned int threadAmount );
	~ChunkWorker();

	void queue( std::shared_ptr< IWorldChunk > chunk, bool priority = false );
	void checkForCrash();

	size_t size();
};

} // namespace Game

#endif
