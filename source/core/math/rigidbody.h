/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_RIGIDBODY_H
#define CUBIX_RIGIDBODY_H

#include "core/cubix_macro.h"
#include "core/math/transform.h"

namespace Core
{

class Rigidbody : public Core::Transform
{
protected:
	float m_airDrag{ 1.0f };
	glm::vec3 m_velocity{ 0.0f };

public:
	CUBIX_GET_SET_CR_CR( m_airDrag, AirDrag );
	CUBIX_GET_SET_CR_CR( m_velocity, Velocity );

	void addVelocity( const glm::vec3& vel );
	void addVelocity( const glm::vec3& vel, const glm::vec3& max );
	void addVelocity( const glm::vec3& vel, const glm::vec3& min, const glm::vec3& max );
	void clampVelocity( const glm::vec3& max );
	void clampVelocity( const glm::vec3& min, const glm::vec3& max );

	void update( float deltaTime );
};

} // namespace Core

#endif
