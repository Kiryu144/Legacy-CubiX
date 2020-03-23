/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_FACING_H
#define CUBIX_FACING_H

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

private:
	unsigned char m_data;

public:
	void setAll( bool enabled );
	void setFace( Face side, bool enabled = true );
	bool hasFace( Face side ) const;
};

} // namespace Core

#endif
