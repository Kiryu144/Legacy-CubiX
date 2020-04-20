/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "stop_watch.h"

namespace Core
{

StopWatch::StopWatch() {}

StopWatch::Timepoint StopWatch::now() const
{
	return std::chrono::steady_clock::now();
}

void StopWatch::start()
{
	m_start = now();
}

void StopWatch::stop()
{
	auto _now	  = now();
	m_timeElapsed = _now - m_start;
	m_start		  = _now;
}

void StopWatch::reset()
{
	m_timeElapsed = m_timeElapsed.zero();
}

float StopWatch::getTimeElapsedMs() const
{
	return std::chrono::duration_cast< std::chrono::microseconds >( m_timeElapsed ).count()
		/ 1000.0f;
}

} // namespace Core