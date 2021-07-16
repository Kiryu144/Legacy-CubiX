#include "helper.h"

namespace Cubix
{
namespace Core
{
namespace GL
{

BindableStateID::BindableStateID( BindFunc bindFunc, DeleteFunc deleteFunc )
	: m_bindFunc( bindFunc ), m_deleteFunc( deleteFunc )
{
}

void BindableStateID::bind( const StateIDHolder* stateHolder )
{
	unsigned int state = stateHolder->getStateID();
	if( state == 0 )
	{
		m_state = 0;
		return;
	}

	if( m_state != state )
	{
		unsigned int type = stateHolder->getTypeID();
		m_bindFunc( state, type );
		m_state = state;
	}
}

void BindableStateID::del( const StateIDHolder* stateHolder )
{
	unsigned int id = stateHolder->getStateID();
	if( id == m_state )
	{
		m_state = 0;
	}

	if( id == 0 )
	{
		return;
	}

	m_deleteFunc( 1, &id );
}

} // namespace GL
} // namespace Core
} // namespace Cubix