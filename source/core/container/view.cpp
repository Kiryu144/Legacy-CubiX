/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "view.h"

#include <glm/ext/matrix_transform.hpp>

namespace Core
{

const glm::mat4& View::getViewMatrix()
{
	if( m_needsUpdate )
	{
		glm::vec3 direction = CreateDirection( m_rotation );
		glm::vec3 front		= { m_position.x + direction.x,
							m_position.y + direction.y,
							m_position.z + direction.z };
		m_matrix			= glm::lookAt( m_position, front, glm::vec3( 0.0f, 1.0f, 0.0f ) );
	}
	return m_matrix;
}

} // namespace Core
