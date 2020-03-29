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
		glm::vec3 direction = CreateDirection( getRotation() );
		glm::vec3 front		= { getPosition().x + direction.x,
							getPosition().y + direction.y,
							getPosition().z + direction.z };
		m_matrix			= glm::lookAt( getPosition(), front, glm::vec3( 0.0f, 1.0f, 0.0f ) );
		m_needsUpdate		= false;
	}
	return getMatrix();
}

} // namespace Core
