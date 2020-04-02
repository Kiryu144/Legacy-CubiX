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

Core::Facing& Voxel::getFacing()
{
	return reinterpret_cast< Core::Facing& >( m_flags );
}

const Core::Facing& Voxel::getFacing() const
{
	return reinterpret_cast< const Core::Facing& >( m_flags );
}

bool Voxel::exists() const
{
	return getFlag( EXISTS );
}

void Voxel::setComplexStructureID( uint8_t id )
{
	( *reinterpret_cast< uint8_t* >( reinterpret_cast< char* >( &m_flags ) + 2 ) ) = id;
}

uint8_t Voxel::getComplexStructureID() const
{
	return (
		*reinterpret_cast< const uint8_t* >( reinterpret_cast< const char* >( &m_flags ) + 2 ) );
}

} // namespace Game
