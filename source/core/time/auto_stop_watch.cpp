/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "auto_stop_watch.h"

#include "core/cubix_log.h"

namespace Core
{

AutoStopWatch::AutoStopWatch( const std::string& name ) : m_name( name )
{
	start();
}

AutoStopWatch::~AutoStopWatch()
{
	stop();
	Core::Logger::Log( "(Stopwatch) " + m_name + " took " + std::to_string( getTimeElapsedMs() )
					   + "ms" );
}

} // namespace Core