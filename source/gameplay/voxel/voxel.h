/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_VOXEL_H
#define CUBIX_VOXEL_H

#include "core/container/color.h"

namespace Gameplay
{

class Voxel : public Core::Color
{
protected:
public:
	Voxel( unsigned char r = 0, unsigned char g = 0, unsigned char b = 0 );
};

} // namespace Gameplay

#endif
