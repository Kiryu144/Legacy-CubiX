/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "performance_monitor.h"

namespace Game
{

PerformanceMonitor::PerformanceMonitor( const std::string& name ) : m_name( name ) {}

PerformanceMonitor::PerformanceMonitor( const PerformanceMonitor& other )
	: m_name( other.m_name ),
	  m_timeNeeded( static_cast< int >( other.m_timeNeeded ) ),
	  m_start( other.m_start )
{
}

PerformanceMonitor::PerformanceMonitor( const PerformanceMonitor&& other )
	: m_name( other.m_name ),
	  m_timeNeeded( static_cast< int >( other.m_timeNeeded ) ),
	  m_start( other.m_start )
{
}

PerformanceMonitor& PerformanceMonitor::operator=( const PerformanceMonitor& other )
{
	m_name		 = other.m_name;
	m_start		 = other.m_start;
	m_timeNeeded = static_cast< int >( other.m_timeNeeded );
	return *this;
}

void PerformanceMonitor::start()
{
	m_start = std::chrono::high_resolution_clock::now();
}

void PerformanceMonitor::stop()
{
	auto now{ std::chrono::high_resolution_clock::now() };
	auto delta{ now - m_start };
	m_timeNeeded = std::chrono::duration_cast< std::chrono::microseconds >( delta ).count();
}

float PerformanceMonitor::getTimeNeededInMilliseconds() const
{
	return getTimeNeededInMicroseconds() / 1000.0f;
}

} // namespace Game