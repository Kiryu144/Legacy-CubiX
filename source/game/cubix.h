/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_H
#define CUBIX_CUBIX_H

#include "game/common/world/world.h"
#include "core/math/transform.h"
#include "game/client/moveable_view.h"
#include "core/opengl/window.h"
#include "core/event.h"
#include "core/math/game_time.h"

struct Cubix : public Core::Listener< Core::EventWindowResize >
{
private:
	Core::Window m_window;
	Core::GameTime m_gameTime;

	glm::mat4 m_projection;

	Game::World m_world;
	Game::MoveableView m_view;

private:
	void update();
	void onEvent( const Core::EventWindowResize& eventType ) override;

public:
	Cubix();
};

#endif
