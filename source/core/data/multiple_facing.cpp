/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "multiple_facing.h"

#include "core/cubix_assert.h"

#include <vector>

namespace Core
{

const std::array< MultipleFacing::Face, 6 > MultipleFacing::Facings{ FRONT, RIGHT, BACK, LEFT, TOP, BOTTOM };

void MultipleFacing::setFace( Face side, bool enabled )
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

bool MultipleFacing::hasFace( Face side ) const
{
	return m_data & side;
}

void MultipleFacing::setAll( bool enabled )
{
	m_data = ( enabled ) ? ( FRONT | RIGHT | BACK | LEFT | TOP | BOTTOM ) : 0;
}

const int MultipleFacing::IndexOf( const MultipleFacing::Face& face )
{
	static const std::vector< int > s_lookup{ -1, 0,  1,  -1, 2,  -1, -1, -1, 3,  -1, -1,
											  -1, -1, -1, -1, -1, 4,  -1, -1, -1, -1, -1,
											  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5 };
	return s_lookup[ static_cast< size_t >( face ) ];
}

MultipleFacing::Face MultipleFacing::ValueOf( int index )
{
	cubix_assert( index >= 0 && index < 6, "Index out of range" );
	return Facings[ index ];
}

} // namespace Core