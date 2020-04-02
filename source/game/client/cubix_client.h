/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_CLIENT_H
#define CUBIX_CUBIX_CLIENT_H

#include "core/net/net_client.h"
#include "core/opengl/window.h"

#include "game/client/moveable_view.h"
#include "game/client/renderer.h"
#include "game/common/cubix.h"

namespace Game
{

class CubixClient : public Cubix,
					public Core::NetClient,
					public Core::Listener< Core::EventWindowResize >,
					public Core::Listener< Core::UserInputHandler::EventUpdate >
{
private:
	Core::Window m_window;
	Renderer m_renderer;

	MoveableView m_moveableView;

	VoxelGroup m_tree1;

	int m_viewDistance{ 12 };

	void update() override;

protected:
	void onPacketReceive( Core::PeerID id, std::istream& istream ) override;
	void onEvent( const Core::EventWindowResize& eventType ) override;
	void onEvent( const Core::UserInputHandler::EventUpdate& eventType ) override;


public:
	CubixClient();
};

} // namespace Game

#endif
