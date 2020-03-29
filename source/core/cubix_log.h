/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_LOG_H
#define CUBIX_CUBIX_LOG_H

// TODO: Rework

#include <atomic>
#include <list>
#include <map>
#include <mutex>
#include <thread>

namespace Core
{

class Logger
{
public:
	enum Loglevel
	{
		INFO,
		WARNING
	};

	struct LogMessage
	{
		Loglevel loglevel;
		std::string message;
		std::thread::id threadID;
	};

private:
	std::mutex m_threadIdentifierMutex;
	std::map< std::thread::id, std::string > m_threadIdentifiers;

	std::atomic_bool m_quit{ false };
	std::list< LogMessage > m_messages;
	std::thread m_workerThread;
	std::mutex m_messagesMutex;

	Logger();
	~Logger();
	void worker();
	static Logger& getInstance();

	void log( Loglevel loglevel, const std::string& message );
	void registerThread( const std::string& name,
						 std::thread::id threadID = std::this_thread::get_id() );

public:
	static void Log( Loglevel loglevel, const std::string& message );
	static void Log( const std::string& message );
	static void Warn( const std::string& message );

	static void Register( const std::string& name,
						  std::thread::id threadID = std::this_thread::get_id() );
	static void UnRegister( std::thread::id threadID = std::this_thread::get_id() );
	static const std::string& GetID( std::thread::id threadID = std::this_thread::get_id() );
};

} // namespace Core

#endif
