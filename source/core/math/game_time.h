/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_GAME_TIME_H
#define CUBIX_GAME_TIME_H

#include <chrono>

namespace Core
{

class GameTime
{
protected:
	typedef std::chrono::microseconds resolution;

	std::chrono::time_point< std::chrono::high_resolution_clock > m_lastUpdate;
	resolution m_deltaTime;
	resolution m_minFrameTime;

public:
	GameTime( unsigned int fpsLimit );

	void update();
	float getFPS() const;
	float getDeltaTime() const;

	void setFPSLimit( unsigned int fpsLimit );
};

} // namespace Core

#endif
