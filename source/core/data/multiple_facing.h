/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_MULTIPLE_FACING_H
#define CUBIX_MULTIPLE_FACING_H

#include <array>
#include <glm/vec3.hpp>

namespace Core
{

class MultipleFacing
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

	static const int IndexOf( const Face& face );
	static Face ValueOf(int index);
	static const glm::vec3& DirectionOf( const Face& face);
	static const std::array< MultipleFacing::Face, 6> Facings;
private:
	unsigned char m_data;

public:
	void setAll( bool enabled );
	void setFace( Face side, bool enabled = true );
	bool hasFace( Face side ) const;
};

} // namespace Core

#endif
