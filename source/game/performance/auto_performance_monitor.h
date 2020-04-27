/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_AUTO_PERFORMANCE_MONITOR_H
#define CUBIX_AUTO_PERFORMANCE_MONITOR_H

namespace Game
{

class PerformanceMonitor;

class AutoPerformanceMonitor
{
protected:
	PerformanceMonitor& m_performanceMonitor;

public:
	AutoPerformanceMonitor( PerformanceMonitor& performanceMonitor );
	~AutoPerformanceMonitor();
};

} // namespace Game

#endif
