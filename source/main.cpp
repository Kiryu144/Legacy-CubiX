/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "game/client/cubix_client.h"
#include "game/server/cubix_server.h"

int main()
{
	Cubix* c;
	std::thread thread( [&c]() {
		Core::Logger::Register( "Server" );
		CubixServer server( 4444 );
		c = &server;
		server.start();
	} );

	Core::Logger::Register( "Client" );
	CubixClient client;
	client.start();

	c->quit();
	thread.join();
	return 0;
}