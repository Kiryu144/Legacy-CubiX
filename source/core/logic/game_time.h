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
	typedef std::chrono::time_point< std::chrono::steady_clock > timepoint;

private:
	timepoint m_lastUpdate;
	resolution m_deltaTime;
	resolution m_minFrameTime;

	timepoint m_lastFPScheck;
	unsigned int m_fps;
	unsigned int m_frameCounter{ 0 };

public:
	GameTime( unsigned int fpsLimit );

	void update();
	unsigned int getFPS() const;
	float getDeltaTime() const;
	double getTimeSinceEpoch() const;

	void setFPSLimit( unsigned int fpsLimit );
};

} // namespace Core

#endif
