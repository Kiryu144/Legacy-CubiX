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
	m_timeElapsed += now() - m_start;
}

void StopWatch::reset()
{
	start();
	m_timeElapsed = m_timeElapsed.zero();
}

} // namespace Core