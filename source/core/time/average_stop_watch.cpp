/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "average_stop_watch.h"

namespace Core
{

AverageStopWatch::AverageStopWatch( size_t samples )
{
	setSampleRate( samples );
}

void AverageStopWatch::setSampleRate( size_t samples )
{
	m_values.resize( samples );
}

void AverageStopWatch::stop()
{
	StopWatch::stop();
	m_average = 0;

	if( getSampleRate() == 0 )
	{
		return;
	}

	for( int i = 1; i < m_values.size(); ++i )
	{
		m_values[ i - 1 ] = m_values[ i ];
		m_average += m_values[ i ];
	}
	m_values[ m_values.size() - 1 ] = getTimeElapsed().count() * 0.001f;
	m_average += m_values[ m_values.size() - 1 ];
	m_average = m_average / m_values.size();

	StopWatch::reset();
}

void AverageStopWatch::reset()
{
	StopWatch::reset();
	m_average = 0;
	std::fill( m_values.begin(), m_values.end(), 0 );
}

size_t AverageStopWatch::getSampleRate() const
{
	return m_values.size();
}

const float* AverageStopWatch::getValues() const
{
	return &m_values[ 0 ];
}

} // namespace Core