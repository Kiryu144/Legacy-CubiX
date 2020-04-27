/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "auto_performance_monitor.h"

#include "game/performance/performance_monitor.h"

namespace Game
{

AutoPerformanceMonitor::AutoPerformanceMonitor( PerformanceMonitor& performanceMonitor )
	: m_performanceMonitor( performanceMonitor )
{
	m_performanceMonitor.start();
}

AutoPerformanceMonitor::~AutoPerformanceMonitor()
{
	m_performanceMonitor.stop();
}

} // namespace Game