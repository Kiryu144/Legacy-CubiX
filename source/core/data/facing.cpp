/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "facing.h"

namespace Core
{

const std::array< Facing::Face, 6 > Facing::Facings{ FRONT, RIGHT, BACK, LEFT, TOP, BOTTOM };

void Facing::setFace( Face side, bool enabled )
{
	if( enabled )
	{
		m_data |= side;
	}
	else
	{
		m_data &= ~side;
	}
}

bool Facing::hasFace( Face side ) const
{
	return m_data & side;
}

void Facing::setAll( bool enabled )
{
	m_data = ( enabled ) ? ( FRONT | RIGHT | BACK | LEFT | TOP | BOTTOM ) : 0;
}

} // namespace Core