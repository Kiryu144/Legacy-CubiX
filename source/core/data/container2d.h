/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CONTAINER2D_H
#define CUBIX_CONTAINER2D_H

#include "core/cubix_assert.h"
#include "core/cubix_macro.h"
#include "core/data/serializeable.h"

#include <vector>

#include <GLM/vec2.hpp>

namespace Core
{

template< typename T >
class Container2D : public Serializeable
{
private:
	std::vector< T > m_data;
	glm::uvec2 m_size;

public:
	inline size_t getIndexForPosition( size_t x, size_t y ) const
	{
		return y * m_size.x + x;
	}

	inline glm::uvec2 getPositionForIndex( size_t index ) const
	{
		return { index % m_size.x, index / m_size.x };
	}

	T& operator[]( size_t index )
	{
		cubix_assert( index < m_data.size(), "Index out of range" );
		return m_data[ index ];
	}

	const T& operator[]( size_t index ) const
	{
		cubix_assert( index < m_data.size(), "Index out of range" );
		return m_data[ index ];
	}

public:
	Container2D( const glm::uvec2& size ) : m_size( size )
	{
		initialize( size );
	}

	void initialize( const glm::uvec2& size )
	{
		m_size = size;
		m_data.resize( size.x * size.y );
	}

	T& operator[]( const glm::uvec2& pos )
	{
		cubix_assert( pos.x < m_size.x && pos.y < m_size.y, "Position out of range" );
		return m_data[ getIndexForPosition( pos.x, pos.y ) ];
	}

	const T& operator[]( const glm::uvec2& pos ) const
	{
		cubix_assert( pos.x < m_size.x && pos.y < m_size.y, "Position out of range" );
		return m_data[ getIndexForPosition( pos.x, pos.y ) ];
	}

	CUBIX_GET_CR( m_size, Size );

	void serialize( std::ostream& out ) const override
	{
		out.write( reinterpret_cast< const char* >( &m_size ), sizeof( decltype( m_size ) ) );
		out.write( reinterpret_cast< const char* >( &m_data.at( 0 ) ),
				   sizeof( T ) * m_data.size() );
	}

	void deserialize( std::istream& in ) override
	{
		in.read( reinterpret_cast< char* >( &m_size ), sizeof( decltype( m_size ) ) );
		initialize( m_size );
		in.read( reinterpret_cast< char* >( &m_data.at( 0 ) ), sizeof( T ) * m_data.size() );
	}
};

} // namespace Core

#endif // CUBIX_CONTAINER2D_H
