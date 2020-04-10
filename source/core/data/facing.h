/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_FACING_H
#define CUBIX_FACING_H

#include <array>

namespace Core
{

class Facing
{
public:
	enum Face : unsigned char
	{
		FRONT  = 1 << 0,
		RIGHT  = 1 << 1,
		BACK   = 1 << 2,
		LEFT   = 1 << 3,
		TOP	   = 1 << 4,
		BOTTOM = 1 << 5
	};

	static const std::array<Facing::Face, 6> Facings;
private:
	unsigned char m_data;

public:
	void setAll( bool enabled );
	void setFace( Face side, bool enabled = true );
	bool hasFace( Face side ) const;
};

} // namespace Core

#endif
