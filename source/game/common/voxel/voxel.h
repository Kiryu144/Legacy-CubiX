/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_VOXEL_H
#define CUBIX_VOXEL_H

#include "core/math/color.h"
#include "core/data/facing.h"

namespace Game
{

class Voxel : public Core::Color
{
public:
	enum Flag : uint64_t
	{
		FACE_FRONT	= 1 << 0,
		FACE_RIGHT	= 1 << 1,
		FACE_BACK	= 1 << 2,
		FACE_LEFT	= 1 << 3,
		FACE_TOP	= 1 << 4,
		FACE_BOTTOM = 1 << 5,
		EXISTS		= 1 << 6,

		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_START = ( uint64_t )1 << 48,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_1	  = ( uint64_t )1 << 49,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_2	  = ( uint64_t )1 << 50,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_3	  = ( uint64_t )1 << 51,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_4	  = ( uint64_t )1 << 52,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_5	  = ( uint64_t )1 << 53,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_6	  = ( uint64_t )1 << 54,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_7	  = ( uint64_t )1 << 55,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_8	  = ( uint64_t )1 << 56,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_9	  = ( uint64_t )1 << 57,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_10	  = ( uint64_t )1 << 58,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_11	  = ( uint64_t )1 << 59,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_12	  = ( uint64_t )1 << 60,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_13	  = ( uint64_t )1 << 61,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_14	  = ( uint64_t )1 << 62,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_END	  = ( uint64_t )1 << 63
	};

protected:
	uint64_t m_flags;

public:
	Voxel() = default;
	Voxel( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 );

	void setFlag( Flag flag, bool b );
	bool getFlag( Flag flag ) const;

	bool exists() const;

	Core::Facing& getFacing();
	const Core::Facing& getFacing() const;
};

} // namespace Game

#endif
