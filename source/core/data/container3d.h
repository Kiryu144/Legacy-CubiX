/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CONTAINER3D_H
#define CUBIX_CONTAINER3D_H

#include "core/cubix_assert.h"

#include <vector>
#include <GLM/vec3.hpp>

namespace Core
{

template< typename T >
class Container3D
{
protected:
	std::vector< T > m_data;
	glm::uvec3 m_size;

	inline size_t getIndexForPosition( size_t x, size_t y, size_t z ) const
	{
		return ( z * m_size.z * m_size.y ) + ( y * m_size.x ) + x;
	}

	inline glm::uvec3 getPositionForIndex( size_t index ) const
	{
		int z = index / ( m_size.x * m_size.y );
		index -= ( z * m_size.x * m_size.y );
		int y = index / m_size.x;
		int x = index % m_size.x;
		return { x, y, z };
	}

public:
	Container3D( const glm::uvec3& size ) : m_size( size )
	{
		initialize( size );
	}

	void initialize( const glm::uvec3& size )
	{
		m_size = size;
		m_data.resize( size.x * size.y * size.z );
	}

	T& operator[]( const glm::uvec3& pos )
	{
		cubix_assert( pos.x < m_size.x && pos.y < m_size.y && pos.z < m_size.z,
					  "Position out of range" );
		return m_data[ getIndexForPosition( pos.x, pos.y, pos.z ) ];
	}

	const T& operator[]( const glm::uvec3& pos ) const
	{
		cubix_assert( pos.x < m_size.x && pos.y < m_size.y && pos.z < m_size.z,
					  "Position out of range" );
		return m_data[ getIndexForPosition( pos.x, pos.y, pos.z ) ];
	}
};

} // namespace Core

#endif