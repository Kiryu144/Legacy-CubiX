/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "moveable_view.h"

#include <c++/4.8.3/iostream>
#include <glfw/glfw3.h>

namespace Game
{

void MoveableView::onEvent( const Core::EventMouseMove& eventType )
{
	glm::vec2 offset{ eventType.x - m_lastMousePosition.x, eventType.y - m_lastMousePosition.y };
	m_turnDirection		= glm::vec2{ -offset.y, offset.x };
	m_lastMousePosition = { eventType.x, eventType.y };
}

void MoveableView::onEvent( const Core::EventKeyPressed& eventType )
{
	static const glm::vec3 s_up{ 0.0f, 1.0f, 0.0f };
	glm::vec3 front
		= Core::Transform::CreateDirection( { 0.0f, getRotation().y, getRotation().z } );

	switch( eventType.key )
	{
	case GLFW_KEY_D:
		m_moveDirection += glm::normalize( glm::cross( front, s_up ) );
		break;
	case GLFW_KEY_A:
		m_moveDirection -= glm::normalize( glm::cross( front, s_up ) );
		break;
	case GLFW_KEY_W:
		m_moveDirection += front;
		break;
	case GLFW_KEY_S:
		m_moveDirection -= front;
		break;
	case GLFW_KEY_LEFT_SHIFT:
		m_moveDirection += glm::vec3{ 0.0f, -1.0f, 0.0f };
		break;
	case GLFW_KEY_SPACE:
		m_moveDirection += glm::vec3{ 0.0f, 1.0f, 0.0f };
		break;
	}
}

void MoveableView::update( double deltaTime )
{
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