/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_NET_INSTANCE_H
#define CUBIX_NET_INSTANCE_H

#include <enet/enet.h>
#include <thread>
#include <atomic>

namespace Game
{

class NetInstance
{
protected:
	ENetHost* m_host;
	std::thread m_worker;
	std::atomic_bool m_quitWorker{ false };

	void initializeEnet();
	void worker();
	void startWorker();

	virtual void onNetworkingEvent( const ENetEvent& event ) {}

public:
	NetInstance( int port ); // Server
	NetInstance();			 // Client
	NetInstance( const NetInstance& other ) = delete;
	virtual ~NetInstance();
};

} // namespace Game

#endif
