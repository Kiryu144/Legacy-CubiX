/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_VOXEL_H
#define CUBIX_VOXEL_H

#include "core/container/color.h"

namespace Game
{

class Voxel : public Core::Color
{
protected:
public:
	Voxel( unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255 );
};

class FlagVoxel : public Voxel
{
public:
	enum class Flag : uint64_t
	{
		EXISTS		   = 1,
		FACE_FLAGS_SET = 2,
		FACE_NORTH	   = 4,
		FACE_EAST	   = 8,
		FACE_SOUTH	   = 16,
		FACE_WEST	   = 32,
		FACE_UP		   = 64,
		FACE_DOWN	   = 128
	};

protected:
	uint64_t m_flags;

public:
	FlagVoxel() = default;

	FlagVoxel( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 );

	void setFlag( Flag flag, bool b );
	bool getFlag( Flag flag ) const;
};

} // namespace Game

#endif
