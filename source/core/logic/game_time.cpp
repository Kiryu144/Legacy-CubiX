/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "game_time.h"

#include "core/cubix_log.h"

#include <string>
#include <thread>

namespace Core
{

GameTime::GameTime( unsigned int fpsLimit )
	: m_lastUpdate( std::chrono::steady_clock::now() ),
	  m_minFrameTime( std::chrono::microseconds( 1000000 / fpsLimit ) ),
	  m_lastFPScheck( m_lastUpdate )
{
}

void GameTime::update()
{
	std::this_thread::sleep_for( m_minFrameTime
								 - ( std::chrono::steady_clock::now() - m_lastUpdate ) );
	auto now	 = std::chrono::steady_clock::now();
	m_deltaTime	 = std::chrono::duration_cast< resolution >( now - m_lastUpdate );
	m_lastUpdate = now;
	++m_frameCounter;
	if( std::chrono::duration_cast< std::chrono::milliseconds >( now - m_lastFPScheck ).count()
		>= 1000 )
	{
		m_fps		   = m_frameCounter;
		m_frameCounter = 0;
		m_lastFPScheck = now;
	}
}

unsigned int GameTime::getFPS() const
{
	return m_fps;
}

float GameTime::getDeltaTime() const
{
	return std::chrono::duration_cast< resolution >( m_deltaTime ).count() / 1000.0f;
}

void GameTime::setFPSLimit( unsigned int fpsLimit )
{
	m_minFrameTime = ( std::chrono::microseconds( 1000000 / fpsLimit ) );
}

double GameTime::getTimeSinceEpoch() const
{
	return m_lastUpdate.time_since_epoch().count() / 1000.0f;
}

} // namespace Core