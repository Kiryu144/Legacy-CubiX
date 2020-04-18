/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "game/cubix_client.h"
#include "game/cubix_server.h"

#include <iostream>

int main()
{
	using namespace Game;
	//Cubix* c;
	//std::thread thread( [&c]() {
	//	Core::Logger::Register( "NetServer" );
		//CubixServer server( 4444 );
		//c = &server;
		//server.start();
	//} );

	Core::Logger::Register( "Client" );
	CubixClient client;
	client.start();

	//c->quit();
	//thread.join();
	return 0;
}