/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "game_time.h"

#include <thread>

namespace Core
{

GameTime::GameTime( unsigned int fpsLimit )
	: m_lastUpdate( std::chrono::high_resolution_clock::now() ),
	  m_minFrameTime( std::chrono::microseconds( 1000000 / fpsLimit ) )
{
}

void GameTime::update()
{
	auto now		= std::chrono::high_resolution_clock::now();
	m_deltaTime		= std::chrono::duration_cast< resolution >( now - m_lastUpdate );
	auto sleep_time = m_minFrameTime - m_deltaTime;

	if( sleep_time.count() > 0 )
	{
		std::this_thread::sleep_for( sleep_time );
		m_deltaTime += sleep_time;
	}

	m_lastUpdate = std::chrono::high_resolution_clock::now();
}

float GameTime::getFPS() const
{
	return 1000000.0f / std::chrono::duration_cast< resolution >( m_deltaTime ).count();
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