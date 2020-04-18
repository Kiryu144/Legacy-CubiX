/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_MOVEABLE_VIEW_H
#define CUBIX_MOVEABLE_VIEW_H

#include "core/cubix_macro.h"
#include "core/event.h"
#include "core/io/user_input_handler.h"
#include "core/math/view.h"

namespace Game
{

class MoveableView : public Core::View, Core::Listener< Core::UserInputHandler::EventUpdate >
{
private:
	glm::vec2 m_lastMousePosition{ 0.0f };
	glm::vec2 m_turnDirection{ 0.0f };
	glm::vec3 m_moveDirection{ 0.0f };

	double m_turnSensitivity = 1.0f;
	double m_moveSpeed		 = 1.0f;

	bool m_active{ false };

	void onEvent( const Core::UserInputHandler::EventUpdate& event ) override;

public:
	void update( double deltaTime );

	CUBIX_GET_SET_CR_CR( m_turnDirection, MouseSensitivity );
	CUBIX_GET_SET_CR_CR( m_moveSpeed, Speed );
	CUBIX_GET_SET_CR_CR( m_active, Active );
};

} // namespace Game

#endif
