#ifndef CUBIX_CORE_HELPER_H
#define CUBIX_CORE_HELPER_H

namespace Cubix
{
namespace Core
{
namespace GL
{

typedef void ( *BindFunc )( unsigned int i1, unsigned int i2 );
typedef void ( *DeleteFunc )( int i1, const unsigned int* i2 );

class StateIDHolder
{
public:
	virtual unsigned int getStateID() const = 0;
	virtual unsigned int getTypeID() const	= 0;
};

class BindableStateID
{
private:
	BindFunc m_bindFunc;
	DeleteFunc m_deleteFunc;

protected:
	unsigned int m_state{ 0 };

public:
	BindableStateID( BindFunc bindFunc, DeleteFunc deleteFunc );

	void bind( const StateIDHolder* stateHolder );
	void del( const StateIDHolder* stateHolder );
};

} // namespace GL
} // namespace Core
} // namespace Cubix

#endif // CUBIX_CORE_HELPER_H
