/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_REGISTRY_H
#define CUBIX_REGISTRY_H

#include "core/cubix_assert.h"

#include <map>
#include <vector>

namespace Core
{

class RegistryKey
{
private:
	size_t m_id;

public:
	RegistryKey( size_t index = static_cast< size_t >( -1 ) ) : m_id( index ){};

	bool isValid() const
	{
		return m_id != static_cast< size_t >( -1 );
	}

	size_t _getKey() const
	{
		return m_id;
	}
};

template< typename T >
class Registry
{
public:
protected:
	std::map< std::string, size_t > m_names;
	std::vector< T > m_data;

public:
	void insert( const std::string& name, const T& t )
	{
		m_data.push_back( t );
		m_names.insert( { name, m_data.size() - 1 } );
	}

	void insert( const std::string& name, T&& t )
	{
		m_data.emplace_back( t );
		m_names.insert( { name, m_data.size() - 1 } );
	}

	std::optional< RegistryKey > getKey( const std::string& name ) const
	{
		auto it = m_names.find( name );
		if( it == m_names.end() )
		{
			return {};
		}
		else
		{
			return { { it->second } };
		}
	}

	T& getValue( RegistryKey key )
	{
		cubix_assert( key.isValid(), "Invalid key" );
		return m_data[ key._getKey() ];
	}

	const T& getValue( RegistryKey key ) const
	{
		cubix_assert( key.isValid(), "Invalid key" );
		return m_data[ key._getKey() ];
	}

	T& getValue( const std::string& name )
	{
		return getValue( getKey( name ).value() );
	}

	const T& getValue( const std::string& name ) const
	{
		return getValue( getKey( name ).value() );
	}
};

} // namespace Core

#endif // CUBIX_REGISTRY_H
