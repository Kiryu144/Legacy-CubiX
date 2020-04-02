/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_VOXEL_H
#define CUBIX_VOXEL_H

#include "core/data/color.h"
#include "core/data/facing.h"

namespace Game
{

class Voxel : public Core::Color
{
public:
	enum Flag : uint64_t
	{
		EXISTS = 1 << 0
	};

protected:
	uint64_t m_flags;

public:
	Voxel() = default;
	Voxel( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 );

	void setFlag( Flag flag, bool b );
	bool getFlag( Flag flag ) const;

	bool exists() const;
};

} // namespace Game

#endif
