/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CHUNK_WORKER_H
#define CUBIX_CHUNK_WORKER_H

#include "core/data/no_copy.h"

#include <atomic>
#include <list>
#include <mutex>
#include <thread>

namespace Game
{

class WorldChunk;

class ChunkWorker : Core::NoCopy
{
public:
	enum OperationType
	{
		GENERATE_TERRAIN,
		GENERATE_FACES,
		GENERATE_MESH
	};

	struct Operation
	{
		std::weak_ptr< WorldChunk > m_worldChunk;
		OperationType m_operationType;
	};

	std::atomic_bool m_quit{ false };
	void worker();

protected:
	std::list< std::thread > m_threads;

	std::mutex m_queueMutex;
	std::list< Operation > m_queue;

public:
	ChunkWorker( unsigned int threadAmount );
	~ChunkWorker();

	void queue( std::shared_ptr< WorldChunk > chunk,
				OperationType operationType,
				bool priority = false );

	size_t size();
};

} // namespace Game

#endif
