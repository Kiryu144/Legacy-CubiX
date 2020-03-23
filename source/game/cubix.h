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

struct Cubix : public Core::Listener< Core::EventWindowResize >
{
private:
	Core::Window m_window;
	Game::World m_world;

	double m_frameStartTime;
	double m_fpsCap;

	glm::mat4 m_projection;
	Game::MoveableView m_view;

private:
	double getCurrentSystemTime() const;
	void waitForForFpsCap();

	void update( double deltaTime );
	void onEvent( const Core::EventWindowResize& eventType ) override;

public:
	Cubix();
};

#endif
