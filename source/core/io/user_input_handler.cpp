/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "user_input_handler.h"

#include "core/event.h"

#include <glfw/glfw3.h>

namespace Core
{

UserInputHandler::UserInputHandler( GLFWwindow* glfwWindow ) : m_glfwWindow( glfwWindow )
{
	m_keysPressedAmount.resize( Key::_SIZE, NOT_PRESSED );
}

bool UserInputHandler::isKey( UserInputHandler::Key key ) const
{
	return key < Key::_SIZE;
}

bool UserInputHandler::isKeyPressed( UserInputHandler::Key key ) const
{
	if( isKey( key ) )
	{
		return m_keysPressedAmount.at( key ) >= JUST_PRESSED;
	}
	return false;
}

bool UserInputHandler::isKeyDown( UserInputHandler::Key key ) const
{
	if( isKey( key ) )
	{
		return m_keysPressedAmount.at( key ) == JUST_PRESSED;
	}
	return false;
}

bool UserInputHandler::isKeyUp( UserInputHandler::Key key ) const
{
	if( isKey( key ) )
	{
		return m_keysPressedAmount.at( key ) == JUST_RELEASED;
	}
	return false;
}

bool UserInputHandler::isCursorLocked() const
{
	return glfwGetInputMode( m_glfwWindow, GLFW_CURSOR ) == GLFW_CURSOR_DISABLED;
}

void UserInputHandler::lockCursor( bool locked )
{
	glfwSetInputMode(
		m_glfwWindow, GLFW_CURSOR, locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL );
}

const glm::vec2& UserInputHandler::getMousePosition()
{
	return m_cursorPosition;
}

void UserInputHandler::update()
{
	for( int i = 0; i < m_keysPressedAmount.size(); ++i )
	{
		KeyState& keyState = m_keysPressedAmount.at( i );
		auto pressed	   = false;

		if( i <= MOUSE_8 )
		{
			pressed = glfwGetMouseButton( m_glfwWindow, i ) == GLFW_PRESS;
		}
		else if( i <= MOUSE_SCROLLWHEEL_DOWN )
		{
			// TODO: Implement
		}
		else
		{
			pressed = glfwGetKey( m_glfwWindow, i ) == GLFW_PRESS;
		}

		if( pressed )
		{
			if( keyState < JUST_PRESSED )
			{
				keyState = JUST_PRESSED;
			}
			else
			{
				keyState = PRESSED;
			}
		}
		else
		{
			if( keyState > JUST_RELEASED )
			{
				keyState = JUST_RELEASED;
			}
			else
			{
				keyState = NOT_PRESSED;
			}
		}
	}

	double x, y;
	glfwGetCursorPos( m_glfwWindow, &x, &y );
	m_cursorPosition = glm::vec2{ x, y };

	Core::Handler< UserInputHandler::EventUpdate >::Fire( { *this } );
}

} // namespace Core