/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_CLIENT_H
#define CUBIX_CUBIX_CLIENT_H

#include "core/io/window.h"
#include "core/net/net_client.h"

#include "game/cubix.h"
#include "game/rendering/moveable_view.h"
#include "game/rendering/renderer.h"
#include "game/world/world.h"

namespace Game
{

class CubixClient : public Cubix, Core::Listener< Core::EventWindowResize >
{
private:
	Core::Window m_window;
	Renderer m_renderer;
	MoveableView m_moveableView;

	Core::NetClient m_client;

	World m_world;

	void update() override;
	void tick() override;
	void onEvent( const Core::EventWindowResize& event ) override;

	void drawImGui();

public:
	CubixClient();
};

} // namespace Game

#endif
