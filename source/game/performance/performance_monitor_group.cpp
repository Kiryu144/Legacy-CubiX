/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "performance_monitor_group.h"

#include "core/cubix_assert.h"

#include "game/performance/performance_monitor.h"

namespace Game
{

PerformanceMonitorGroup::PerformanceMonitorGroup( const std::string& baseName )
	: m_baseName( baseName )
{
}

PerformanceMonitorGroup::PerformanceMonitorGroup( const std::string& name, size_t amount )
{
	for( int i = 0; i < amount; ++i )
	{
		m_performanceMonitors.emplace_back( name + "_" + std::to_string( i ) );
	}
}

void PerformanceMonitorGroup::resize( size_t size )
{
	if( size > m_performanceMonitors.size() )
	{
		size_t startSize = m_performanceMonitors.size();
		size_t amount{ size - startSize };
		for( int i = 0; i < amount; ++i )
		{
			m_performanceMonitors.emplace_back( m_baseName + "_"
												+ std::to_string( startSize + i ) );
		}
	}
	else if( size < m_performanceMonitors.size() )
	{
		m_performanceMonitors.erase( m_performanceMonitors.begin() + size,
									 m_performanceMonitors.end() );
	}
}

PerformanceMonitor& PerformanceMonitorGroup::operator[]( size_t index )
{
	cubix_assert( index < m_performanceMonitors.size(), "Index out of bounds" );
	return m_performanceMonitors[ index ];
}

float PerformanceMonitorGroup::getMeanTimeInMilliseconds() const
{
	float mean{ 0 };
	float samples{ 0 };
	for( auto& counter : m_performanceMonitors )
	{
		auto time{ counter.getTimeNeededInMilliseconds() };
		if( time > 0 )
		{
			mean += time;
			++samples;
		}
	}

	return samples > 0 ? mean / samples : 0.0f;
}

} // namespace Game