/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_log.h"

#include "cubix_assert.h"

#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Core
{

Logger::Logger() : m_workerThread( &Logger::worker, this ) {}

Logger& Logger::getInstance()
{
	static Logger logger;
	return logger;
}

Logger::~Logger()
{
	m_quit = true;
	m_workerThread.join();
}

void Logger::worker()
{
	std::ofstream file( "log.log", std::ios::binary | std::ios::app );
	cubix_assert( file.is_open(), "Unable to open log file." );
	file << "============ PROGRAM START ==============" << std::endl;

	static const char* logLevelStrings[ 4 ] = { "[INFO]", "[WARNING]", "[ASSERT]", "[UNDEFINED]" };
	static const char* format				= "[%H:%M:%S]";
	char formattedTimeBuffer[ 64 ];
	while( !m_quit )
	{
		std::list< LogMessage > messages;
		{
			std::lock_guard< std::mutex > lockGuard( m_messagesMutex );
			if( m_messages.empty() )
			{
				continue;
			}
			messages = m_messages;
			m_messages.clear();
		}

		const std::time_t now	= std::time( 0 );
		const std::tm* exploded = std::localtime( &now );
		std::strftime( formattedTimeBuffer, 64, format, exploded );

		for( const auto& message : messages )
		{
			const char* logLevelString = ( message.loglevel >= 0 && message.loglevel < 3 ) ?
				logLevelStrings[ message.loglevel ] :
				logLevelStrings[ 3 ];

			std::stringstream ss;
			ss << formattedTimeBuffer << logLevelString << " " << message.message;
			std::string msg = ss.str();

			std::cout << msg << std::endl;
			file << msg << std::endl;
		}
		messages.clear();

		std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );
	}

	file << "============ PROGRAM STOP ===============" << std::endl;
}

void Logger::log( Logger::Loglevel loglevel, const std::string& message )
{
	std::lock_guard< std::mutex > lockGuard( m_messagesMutex );
	m_messages.push_back( { loglevel, message } );
}

void Logger::Log( Logger::Loglevel loglevel, const std::string& message )
{
	getInstance().log( loglevel, message );
}

void Logger::Log( const std::string& message )
{
	Log( Loglevel::INFO, message );
}

} // namespace Core