/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_WORKER_H
#define CUBIX_WORLD_CHUNK_WORKER_H

#include <list>
#include <mutex>
#include <mingw.thread.h>
#include <mingw.mutex.h>
#include <vector>

namespace Game
{

class WorldChunk;

class WorldChunkWorker
{
public:
	enum Action
	{
		GENERATE,
		POPULATE,
		MESH
	};

protected:
	struct Operation
	{
		Action action;
		std::shared_ptr< WorldChunk > chunk;
	};

protected:
	bool m_quit{ false };
	std::vector< std::thread > m_threads;

	std::recursive_mutex m_queueMutex;
	std::list< Operation > m_queue;

	void worker( int index );

public:
	WorldChunkWorker( size_t threads );
	~WorldChunkWorker();

	void queue( std::shared_ptr< WorldChunk >& chunk, Action action );
};

} // namespace Game

#endif
