/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_AUTO_STOP_WATCH_H
#define CUBIX_AUTO_STOP_WATCH_H

#include "core/time/stop_watch.h"

#include <string>

namespace Core
{

class AutoStopWatch : public StopWatch
{
protected:
	std::string m_name;

public:
	AutoStopWatch( const std::string& name );
	~AutoStopWatch();
};

} // namespace Core

#endif
