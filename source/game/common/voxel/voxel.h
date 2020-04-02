/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_VOXEL_H
#define CUBIX_VOXEL_H

#include "core/data/facing.h"
#include "core/math/color.h"

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

		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_START = ( uint64_t )1 << 16,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_1	  = ( uint64_t )1 << 17,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_2	  = ( uint64_t )1 << 18,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_3	  = ( uint64_t )1 << 19,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_4	  = ( uint64_t )1 << 20,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_5	  = ( uint64_t )1 << 21,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_6	  = ( uint64_t )1 << 22,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_7	  = ( uint64_t )1 << 23,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_8	  = ( uint64_t )1 << 24,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_9	  = ( uint64_t )1 << 25,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_10	  = ( uint64_t )1 << 26,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_11	  = ( uint64_t )1 << 27,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_12	  = ( uint64_t )1 << 28,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_13	  = ( uint64_t )1 << 29,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_14	  = ( uint64_t )1 << 30,
		COMPLEX_VOXEL_STRUCTURE_PLACEHOLDER_END	  = ( uint64_t )1 << 31
	};

protected:
	uint64_t m_flags;

public:
	Voxel() = default;
	Voxel( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 );

	void setFlag( Flag flag, bool b );
	bool getFlag( Flag flag ) const;

	bool exists() const;

	void setComplexStructureID( uint8_t id );
	uint8_t getComplexStructureID() const;

	Core::Facing& getFacing();
	const Core::Facing& getFacing() const;
};

} // namespace Game

#endif
