/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "game/client/cubix_client.h"
#include "game/server/cubix_server.h"

int main()
{
	CubixServer server( 4444 );
	std::thread thread( [&server]() {
		Core::Logger::Register( "SERVER" );
		server.start();
	} );

	Core::Logger::Register( "CLIENT" );
	CubixClient client;
	client.start();

	server.quit();
	thread.join();
	return 0;
}