/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix.h"

#include <GLM/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <thread>

Cubix::Cubix() : m_window( 1440, 900, "CubiX" ), m_world(), m_gameTime( 1000 )
{
	int range = 3;
	for( int x = -range; x <= range; ++x )
	{
		for( int z = -range; z <= range; ++z )
		{
			m_world.loadOrCreate( { x, 0, z } );
		}
	}

	while( !m_window.shouldClose() )
	{
		update();
	}
}

void Cubix::update()
{
	m_gameTime.update();
	Core::Window::Update();
	m_window.swap();

	m_view.update( m_gameTime.getDeltaTime() );

	m_world.draw( m_view.getViewMatrix(), m_projection );
}

void Cubix::onEvent( const Core::EventWindowResize& eventType )
{
	m_projection = glm::perspective(
		glm::radians( 70.0f ), static_cast< float >( eventType.w ) / eventType.h, 0.1f, 1000.0f );
}