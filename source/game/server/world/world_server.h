/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_SERVER_H
#define CUBIX_WORLD_SERVER_H

#include "core/net/net_server.h"

#include "game/common/world/world.h"

namespace Game
{

class WorldServer : public World
{
protected:
	std::mutex m_generationQueueMutex;

	std::list< std::weak_ptr< WorldChunk > > m_generationQueue;

	std::atomic_bool m_quit{ false };
	std::list< std::thread > m_worker;

	void spawnWorker( size_t amount );
	void worker();

public:
	WorldServer();
	~WorldServer();
	void loadOrCreate( const glm::ivec3& position );
	void update( float deltaTime ) override;
};

} // namespace Game

#endif
