/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_VIEW_H
#define CUBIX_VIEW_H

#include "core/container/transform.h"

namespace Core
{

class View : public Transform
{
protected:
public:
	const glm::mat4& getViewMatrix();
};

} // namespace Core

#endif
