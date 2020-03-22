/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "voxel.h"

namespace Game
{

Voxel::Voxel( unsigned char r, unsigned char g, unsigned char b, unsigned char a )
	: Core::Color( r, g, b, a )
{
}

FlagVoxel::FlagVoxel( unsigned char r, unsigned char g, unsigned char b, unsigned char a )
{
	setFlag( Flag::EXISTS, true );
}

void FlagVoxel::setFlag( FlagVoxel::Flag flag, bool b )
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

bool FlagVoxel::getFlag( FlagVoxel::Flag flag ) const
{
	return m_flags & static_cast< uint64_t >( flag );
}

} // namespace Game
