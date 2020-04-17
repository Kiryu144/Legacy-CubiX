/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_IMGUI_PERFORMANCE_COUNTER_H
#define CUBIX_IMGUI_PERFORMANCE_COUNTER_H

#include "core/logic/lockable.h"
#include "core/logic/singelton.h"
#include "core/time/average_stop_watch.h"

namespace Game
{

class ImguiPerformanceCounter : public Core::Singelton< ImguiPerformanceCounter >
{
protected:
	Core::AverageStopWatch m_frameTime{ 30 };

public:
	void draw();

	CUBIX_GET_R_CR( m_frameTime, FrameTime );
};

} // namespace Game

#endif
