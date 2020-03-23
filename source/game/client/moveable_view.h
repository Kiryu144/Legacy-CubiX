/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_MOVEABLE_VIEW_H
#define CUBIX_MOVEABLE_VIEW_H

#include "core/container/view.h"
#include "core/event.h"
#include "core/opengl/window.h"

namespace Game
{

class MoveableView : public Core::View,
					 Core::Listener< Core::EventMouseMove >,
					 Core::Listener< Core::EventKeyPressed >
{
private:
	glm::vec2 m_lastMousePosition{ 0.0f };

	glm::vec2 m_turnDirection{ 0.0f };
	glm::vec3 m_moveDirection{ 0.0f };

	double m_turnSensitivity = 1.0f;
	double m_moveSpeed		 = 1.0f;

	void onEvent( const Core::EventMouseMove& eventType ) override;
	void onEvent( const Core::EventKeyPressed& eventType ) override;

public:
	void update( double deltaTime );
};

} // namespace Game

#endif
