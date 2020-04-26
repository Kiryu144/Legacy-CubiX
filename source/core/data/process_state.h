/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PROCESS_STATE_H
#define CUBIX_PROCESS_STATE_H

namespace Core
{

class ProcessState
{
public:
	enum State : unsigned char
	{
		TODO		= 0,
		IN_PROGRESS = 1,
		FINISHED	= 2
	};

protected:
	unsigned char m_state;

public:
	inline void setState( State state )
	{
		m_state = state;
	}

	inline State getState() const
	{
		return static_cast< State >( m_state );
	}

	inline bool is( State state ) const
	{
		return getState() == state;
	}
};

} // namespace Core

#endif // CUBIX_PROCESS_STATE_H
