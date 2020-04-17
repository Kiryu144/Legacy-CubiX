/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_AVERAGE_STOP_WATCH_H
#define CUBIX_AVERAGE_STOP_WATCH_H

#include "core/time/stop_watch.h"

#include <vector>

namespace Core
{

class AverageStopWatch : public StopWatch
{
protected:
	std::vector< float > m_values;
	float m_average{ 0 };

public:
	AverageStopWatch( size_t samples );

	void setSampleRate( size_t samples );
	size_t getSampleRate() const;

	CUBIX_GET_CR( m_average, AverageMs );
	const float* getValues() const;

	void stop() override;
	void reset() override;
};

} // namespace Core

#endif
