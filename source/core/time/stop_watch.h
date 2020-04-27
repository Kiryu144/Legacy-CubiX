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
	Duration m_timeElapsed{ 0 };

	Timepoint now() const;

public:
	StopWatch();
	virtual ~StopWatch() = default;

	virtual void start();
	virtual void stop();
	virtual void reset();

	virtual float getTimeElapsedMs() const;
};

} // namespace Core

#endif
