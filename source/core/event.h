/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_EVENT_H
#define CUBIX_EVENT_H

#include <set>
#include <memory>

namespace Core
{

template< typename EventType >
class Listener;

template< typename EventType >
class Handler
{
public:
	typedef Listener< EventType >* listener_t;

private:
	friend class Listener< EventType >;

	static std::set< listener_t > s_listener;

	static void add( listener_t listener )
	{
		s_listener.insert( listener );
	}

	static void remove( listener_t listener )
	{
		s_listener.erase( listener );
	}

	static size_t size()
	{
		return s_listener.size();
	}

public:
	Handler() = delete;

	static void Fire( const EventType& event );
};

template< typename EventType >
class Listener
{
public:
	Listener()
	{
		Handler< EventType >::add( this );
	}

	Listener( const Listener& other )
	{
		Handler< EventType >::add( this );
	}

	virtual ~Listener()
	{
		Handler< EventType >::remove( this );
	}

	virtual void onEvent( const EventType& eventType ) = 0;
};

template< typename EventType >
std::set< typename Core::Handler< EventType >::listener_t > Handler< EventType >::s_listener;

template< typename EventType >
void Handler< EventType >::Fire( const EventType& event )
{
	for( auto& listener : Handler< EventType >::s_listener )
	{
		listener->onEvent( event );
	}
}

} // namespace Core

#endif // CUBIX_EVENT_H
