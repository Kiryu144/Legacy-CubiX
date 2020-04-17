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
public:
	const glm::mat4& getViewMatrix();
};

} // namespace Core

#endif
