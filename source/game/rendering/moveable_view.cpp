/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "moveable_view.h"

namespace Game
{

void MoveableView::onEvent( const Core::UserInputHandler::EventUpdate& event )
{
	if( event.instance.isKeyDown( Core::UserInputHandler::F1 ) )
	{
		m_active = !m_active;
		event.instance.lockCursor( m_active );

		if( m_active )
		{
			m_lastMousePosition = event.instance.getMousePosition();
		}
	}

	if( !m_active )
	{
		return;
	}

	glm::vec2 offset{ event.instance.getMousePosition().x - m_lastMousePosition.x,
	                  event.instance.getMousePosition().y - m_lastMousePosition.y };
	m_turnDirection = glm::vec2{ -offset.y, offset.x };
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

void MoveableView::update( double deltaTime )
{
	if( !m_active )
	{
		return;
	}

	getPosition() += glm::vec3{ m_moveDirection.x * 0.01 * deltaTime * m_moveSpeed,
	                            m_moveDirection.y * 0.01 * deltaTime * m_moveSpeed,
	                            m_moveDirection.z * 0.01 * deltaTime * m_moveSpeed };

	getRotation() += glm::vec3{ m_turnDirection.x * 0.1 * m_turnSensitivity,
	                            m_turnDirection.y * 0.1 * m_turnSensitivity,
	                            0.0f };

	getRotation().x = glm::clamp( getRotation().x, -89.9f, 89.0f );

	m_moveDirection = { 0.0, 0.0, 0.0 };
	m_turnDirection = { 0.0, 0.0 };
}

} // namespace Game