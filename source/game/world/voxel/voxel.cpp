/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "voxel.h"

namespace Game
{

Voxel::Voxel( unsigned char r, unsigned char g, unsigned char b, unsigned char a )
	: Core::Color( r, g, b, a )
{
	setFlag( Flag::EXISTS, true );
}

void Voxel::setFlag( Voxel::Flag flag, bool b )
{
	if( b )
	{
		m_flags |= static_cast< uint64_t >( flag );
	}
	else
	{
		m_flags &= ~static_cast< uint64_t >( flag );
	}
}

bool Voxel::getFlag( Voxel::Flag flag ) const
{
	return m_flags & static_cast< uint64_t >( flag );
}

bool Voxel::exists() const
{
	return getFlag( EXISTS );
}

} // namespace Game
