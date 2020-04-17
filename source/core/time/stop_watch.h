/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_STOP_WATCH_H
#define CUBIX_STOP_WATCH_H

#include "core/cubix_macro.h"

#include <chrono>

namespace Core
{

class StopWatch
{
private:
	typedef std::chrono::microseconds Resolution;
	typedef std::chrono::time_point< std::chrono::steady_clock > Timepoint;
	typedef std::chrono::steady_clock::duration Duration;

protected:
	Timepoint m_start;
	Duration m_timeElapsed;

	Timepoint now() const;

public:
	StopWatch();

	CUBIX_GET_CR( m_start, Start );
	CUBIX_GET_CR( m_timeElapsed, TimeElapsed );

	virtual void start();
	virtual void stop();
	virtual void reset();
};

} // namespace Core

#endif
