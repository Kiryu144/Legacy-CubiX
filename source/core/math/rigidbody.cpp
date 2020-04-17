/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "rigidbody.h"

namespace Core
{

void Rigidbody::update( float deltaTime )
{
	glm::vec3 normalized{ glm::normalize( m_velocity ) };
	for( int i = 0; i < 3; ++i )
	{
		if( m_velocity[ i ] != 0 )
		{
			float drag = normalized[ i ] * m_airDrag * deltaTime;
			if( abs( drag ) > abs( m_velocity[ i ] ) )
			{
				m_velocity[ i ] = 0;
			}
			else
			{
				m_velocity[ i ] -= drag;
			}
		}

		getPosition()[ i ] += m_velocity[ i ] * deltaTime;
	}
}

void Rigidbody::addVelocity( const glm::vec3& vel )
{
	m_velocity += vel;
}

void Rigidbody::addVelocity( const glm::vec3& vel, const glm::vec3& max )
{
	m_velocity = glm::clamp( m_velocity + vel, max * glm::vec3( -1.0 ), max );
}

void Rigidbody::addVelocity( const glm::vec3& vel, const glm::vec3& min, const glm::vec3& max )
{
	m_velocity = glm::clamp( m_velocity + vel, min, max );
}

void Rigidbody::clampVelocity( const glm::vec3& max )
{
	glm::clamp( m_velocity, max * glm::vec3( -1.0 ), max );
}

void Rigidbody::clampVelocity( const glm::vec3& min, const glm::vec3& max )
{
	glm::clamp( m_velocity, min, max );
}

} // namespace Core