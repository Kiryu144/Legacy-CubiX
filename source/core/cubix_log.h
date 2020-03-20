/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_LOG_H
#define CUBIX_CUBIX_LOG_H

#include <thread>
#include <atomic>
#include <mutex>
#include <list>

namespace Core
{

class Logger
{
public:
	enum Loglevel
	{
		INFO,
		WARNING,
		ASSERT
	};
	struct LogMessage
	{
		Loglevel loglevel;
		std::string message;
	};

private:
	std::atomic_bool m_quit{ false };
	std::list< LogMessage > m_messages;
	std::thread m_workerThread;
	std::mutex m_messagesMutex;

	Logger();
	~Logger();
	void worker();
	static Logger& getInstance();

	void log( Loglevel loglevel, const std::string& message );

public:
	static void Log( Loglevel loglevel, const std::string& message );
	static void Log( const std::string& message );
};

} // namespace Core

#endif
