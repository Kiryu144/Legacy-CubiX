/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "player_controller.h"

#include "core/math/transform.h"

#include "game/world/entity/player.h"

namespace Game
{

PlayerController::PlayerController( std::shared_ptr< Player > player ) : m_player( player ) {}

void PlayerController::updateView()
{

	//m_view.getRotation().y = glm::degrees(m_player->getRotation().y);
	//m_view.getPosition()
		//= Core::Transform::CreateDirection( m_player->getRotation() ) * glm::vec3( -10.0f ) + glm::vec3(0.0f, 5.0f, 0.0f);
}

void PlayerController::update( double deltaTime )
{
	m_player->getPosition() += glm::vec3{ m_moveDirection.x * 0.01 * deltaTime * m_moveSpeed,
										  0.0f,
										  m_moveDirection.z * 0.01 * deltaTime * m_moveSpeed };

	m_player->getRotation() += glm::vec3{ m_mouseMove.x * 0.1 * m_turnSensitivity,
										  m_mouseMove.y * 0.1 * m_turnSensitivity,
										  0.0f };

	m_player->getRotation().x = glm::clamp( getRotation().x, -89.9f, 89.0f );

	m_moveDirection = { 0.0, 0.0, 0.0 };
	m_mouseMove		= { 0.0, 0.0 };
}

void PlayerController::onEvent( const Core::UserInputHandler::EventUpdate& event )
{
	glm::vec2 offset{ event.instance.getMousePosition().x - m_lastMousePosition.x,
					  event.instance.getMousePosition().y - m_lastMousePosition.y };
	m_mouseMove = glm::vec2{ -offset.y, offset.x };
	m_lastMousePosition
		= { event.instance.getMousePosition().x, event.instance.getMousePosition().y };

	static const glm::vec3 s_up{ 0.0f, 1.0f, 0.0f };
	glm::vec3 front
		= Core::Transform::CreateDirection( { 0.0f, getRotation().y, getRotation().z } );

	if( event.instance.isKeyPressed( Core::UserInputHandler::D ) )
	{
		m_moveDirection += glm::normalize( glm::cross( front, s_up ) );
	}

	if( event.instance.isKeyPressed( Core::UserInputHandler::A ) )
	{
		m_moveDirection -= glm::normalize( glm::cross( front, s_up ) );
	}

	if( event.instance.isKeyPressed( Core::UserInputHandler::W ) )
	{
		m_moveDirection += front;
	}

	if( event.instance.isKeyPressed( Core::UserInputHandler::S ) )
	{
		m_moveDirection -= front;
	}

	if( event.instance.isKeyPressed( Core::UserInputHandler::LEFT_SHIFT ) )
	{
		m_moveDirection += glm::vec3{ 0.0f, -1.0f, 0.0f };
	}

	if( event.instance.isKeyPressed( Core::UserInputHandler::SPACE ) )
	{
		m_moveDirection += glm::vec3{ 0.0f, 1.0f, 0.0f };
	}
}

} // namespace Game