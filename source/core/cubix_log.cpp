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
	do
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

			std::string threadPrefix = "";
			{
				std::lock_guard< std::mutex > lockGuard( m_messagesMutex );
				auto it = m_threadIdentifiers.find( message.threadID );
				if( it != m_threadIdentifiers.end() )
				{
					threadPrefix = it->second;
				}
			}

			std::stringstream ss;
			ss << formattedTimeBuffer << logLevelString;
			if( !threadPrefix.empty() )
			{
				ss << "[" << threadPrefix << "]";
			}
			ss << " " << message.message;
			std::string msg = ss.str();

			std::cout << msg << std::endl;
			file << msg << std::endl;
		}
		messages.clear();

		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
	} while( !m_quit );

	file << "============ PROGRAM STOP ===============" << std::endl;
}

void Logger::log( Logger::Loglevel loglevel, const std::string& message )
{
	std::lock_guard< std::mutex > lockGuard( m_messagesMutex );
	m_messages.push_back( { loglevel, message, std::this_thread::get_id() } );
}

void Logger::registerThread( const std::string& name, std::thread::id threadID )
{
	std::lock_guard< std::mutex > guard( m_threadIdentifierMutex );
	if( name.empty() )
	{
		m_threadIdentifiers.erase( threadID );
	}
	else
	{
		m_threadIdentifiers[ threadID ] = name;
	}
}

void Logger::Log( Logger::Loglevel loglevel, const std::string& message )
{
	getInstance().log( loglevel, message );
}

void Logger::Log( const std::string& message )
{
	Log( Loglevel::INFO, message );
}

void Logger::Register( const std::string& name, std::thread::id threadID )
{
	getInstance().registerThread( name, threadID );
}

void Logger::UnRegister( std::thread::id threadID )
{
	getInstance().registerThread( "", threadID );
}

const std::string& Logger::GetID( std::thread::id threadID )
{
	static const std::string empty = "";
	auto it						   = getInstance().m_threadIdentifiers.find( threadID );
	return it != getInstance().m_threadIdentifiers.end() ? it->second : empty;
}

} // namespace Core
