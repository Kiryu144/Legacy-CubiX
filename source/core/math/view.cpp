/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "view.h"

#include <glm/ext/matrix_transform.hpp>

namespace Core
{

const glm::mat4& View::getViewMatrix()
{
	if( needsUpdate() )
	{
		m_direction	  = CreateDirection( getRotation() );
		m_front		  = { getPosition().x + m_direction.x,
					  getPosition().y + m_direction.y,
					  getPosition().z + m_direction.z };
		m_matrix	  = glm::lookAt( getPosition(), m_front, glm::vec3( 0.0f, 1.0f, 0.0f ) );
		m_needsUpdate = false;
	}
	return getMatrix();
}

} // namespace Core
