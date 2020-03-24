/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "game/client/cubix_client.h"
#include "game/server/cubix_server.h"

int main()
{
	Cubix* c;
	std::thread thread( [&c]() {
		CubixServer server( 4444 );
		c = &server;
		server.start();
	} );

	CubixClient client;
	client.start();

	c->quit();
	thread.join();
	return 0;
}