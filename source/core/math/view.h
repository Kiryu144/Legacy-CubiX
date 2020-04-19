/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_VIEW_H
#define CUBIX_VIEW_H

#include "core/math/rigidbody.h"

namespace Core
{

class View : public Rigidbody
{
protected:
	glm::vec3 m_front;
	glm::vec3 m_direction;

public:
	const glm::mat4& getViewMatrix();

	CUBIX_GET_CR( m_front, Front );
	CUBIX_GET_CR( m_direction, Direction );
};

} // namespace Core

#endif
