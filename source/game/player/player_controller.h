/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PLAYER_CONTROLLER_H
#define CUBIX_PLAYER_CONTROLLER_H

#include "core/event.h"
#include "core/io/user_input_handler.h"
#include "core/math/view.h"

#include <memory>

namespace Game
{

class Player;

class PlayerController : public Core::Listener< Core::UserInputHandler::EventUpdate >
{
protected:
	std::shared_ptr< Player > m_player;
	Core::View m_view;

	glm::vec3 m_moveDirection{ 0.0f };
	glm::vec2 m_lastMousePosition{ 0.0f };
	glm::vec2 m_mouseMove{ 0.0f };
	bool m_jump{ false };

	float m_mouseSensitivity = 1.0f;
	float m_moveSpeed		 = 1.0f;
	float m_jumpStrength	 = 1.0f;

	void onEvent( const Core::UserInputHandler::EventUpdate& eventType ) override;

public:
	PlayerController( std::shared_ptr< Player > player );

	CUBIX_GET_R_CR( m_player, Player );
	CUBIX_GET_R_CR( m_view, View );
	CUBIX_GET_SET_CR_CR( m_mouseSensitivity, MouseSensitivity );
	CUBIX_GET_SET_CR_CR( m_moveSpeed, MoveSpeed );
	CUBIX_GET_SET_CR_CR( m_jumpStrength, JumpStrength );

	void update( double deltaTime );
};

} // namespace Game

#endif
