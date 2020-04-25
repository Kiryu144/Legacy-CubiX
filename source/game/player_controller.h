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

class PlayerController : public Core::View, Core::Listener< Core::UserInputHandler::EventUpdate >
{
protected:
	std::shared_ptr< Player > m_player;
	Core::View m_view;

	glm::vec3 m_moveDirection{ 0.0f };
	glm::vec2 m_lastMousePosition{ 0.0f };
	glm::vec2 m_mouseMove{ 0.0f };

	double m_turnSensitivity = 1.0f;
	double m_moveSpeed		 = 1.0f;

	void onEvent( const Core::UserInputHandler::EventUpdate& eventType ) override;

public:
	PlayerController( std::shared_ptr< Player > player );

	CUBIX_GET_R_CR( m_player, Player );
	CUBIX_GET_R_CR( m_view, View );

	void updateView();
	void update( double deltaTime );
};

} // namespace Game

#endif
