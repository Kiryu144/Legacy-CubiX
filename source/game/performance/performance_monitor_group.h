/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PERFORMANCE_MONITOR_GROUP_H
#define CUBIX_PERFORMANCE_MONITOR_GROUP_H

#include <string>
#include <vector>

namespace Game
{

class PerformanceMonitor;

class PerformanceMonitorGroup
{
protected:
	std::string m_baseName;
	std::vector< PerformanceMonitor > m_performanceMonitors;

public:
	PerformanceMonitorGroup( const std::string& baseName );
	PerformanceMonitorGroup( const std::string& name, size_t amount );

	void resize( size_t size );
	PerformanceMonitor& operator[]( size_t index );

	// Returns the mean time of all performance monitors
	// Note that monitors with a recorded zero time won't be calculated
	float getMeanTimeInMilliseconds() const;
};

} // namespace Game

#endif
