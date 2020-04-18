/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_VOXEL_H
#define CUBIX_VOXEL_H

#include "core/data/color.h"
#include "core/data/multiple_facing.h"

namespace Game
{

class Voxel : public Core::Color
{
public:
	enum Flag : unsigned char
	{
		EXISTS		= 1 << 0,
		UNDEFINED_1 = 1 << 1,
		UNDEFINED_2 = 1 << 2,
		UNDEFINED_3 = 1 << 3,
		UNDEFINED_4 = 1 << 4,
		UNDEFINED_5 = 1 << 5,
		UNDEFINED_6 = 1 << 6,
		UNDEFINED_7 = 1 << 7,
	};

protected:
	uint64_t m_flags{ 0 };

public:
	Voxel() = default;
	Voxel( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 );

	void setFlag( Flag flag, bool b );
	bool getFlag( Flag flag ) const;

	bool exists() const;
};

} // namespace Game

#endif
