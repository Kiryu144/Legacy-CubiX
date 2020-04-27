/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PERFORMANCE_MONITOR_H
#define CUBIX_PERFORMANCE_MONITOR_H

#include "core/cubix_macro.h"

#include <atomic>
#include <chrono>
#include <string>

namespace Game
{

class PerformanceMonitor
{
protected:
	// The name of the monitor. Used to display the results.
	std::string m_name{ "unnamed" };

	// Time needed for last run in microseconds
	std::atomic_int m_timeNeeded{ 0 };

	// Time of last start() or stop() call
	std::chrono::time_point< std::chrono::high_resolution_clock > m_start;

public:
	PerformanceMonitor( const std::string& name );
	PerformanceMonitor( const PerformanceMonitor& other);
	PerformanceMonitor( const PerformanceMonitor&& other);
	PerformanceMonitor& operator=(const PerformanceMonitor& other);

	CUBIX_GET_CR( m_timeNeeded, TimeNeededInMicroseconds );
	float getTimeNeededInMilliseconds() const;

	void start();
	void stop();
};

} // namespace Game

#endif
