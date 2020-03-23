/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix.h"

#include <GLM/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <thread>

Cubix::Cubix()
	: m_window( 1440, 900, "CubiX" ),
	  m_world(),
	  m_frameStartTime( getCurrentSystemTime() ),
	  m_fpsCap( 240.0 )
{
	int range = 3;
	for( int x = -range; x <= range; ++x )
	{
		for( int z = -range; z <= range; ++z )
		{
			m_world.loadOrCreate( { x, 0, z } );
		}
	}

	m_view.getPosition() = { 0.0f, 20.0f, 0.0f };

	while( !m_window.shouldClose() )
	{
		double now		 = getCurrentSystemTime();
		double delta	 = now - m_frameStartTime;
		m_frameStartTime = now;
		update( delta );
	}
}

void Cubix::update( double deltaTime )
{
	Core::Window::Update(); // Update glfw events
	m_window.swap();		// Refresh frame

	m_view.getRotation() += glm::vec3{ 0.0f, 0.001f * deltaTime, 0.0f };

	m_world.draw( m_view, m_projection );

	// Has to be at the end
	waitForForFpsCap();
}

void Cubix::onEvent( const Core::EventWindowResize& eventType )
{
	m_projection = glm::perspective(
		80.0f, static_cast< float >( eventType.w ) / eventType.h, 0.1f, 1000.0f );
}

void Cubix::waitForForFpsCap()
{
	if( m_fpsCap <= 0.0 )
	{
		return;
	}

	double frameTimeTillNow = m_frameStartTime - getCurrentSystemTime();
	double minFrameTime		= 1000.0 / m_fpsCap;
	std::this_thread::sleep_for(
		std::chrono::milliseconds( static_cast< uint64_t >( minFrameTime - frameTimeTillNow ) ) );
}

double Cubix::getCurrentSystemTime() const
{
	return glfwGetTime() * 1000.0;
}
