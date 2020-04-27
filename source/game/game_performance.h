/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_GAME_PERFORMANCE_H
#define CUBIX_GAME_PERFORMANCE_H

#include "game/performance/performance_monitor.h"
#include "game/performance/performance_monitor_group.h"

namespace Game
{

class GamePerformanceCounter
{
protected:
	PerformanceMonitor m_frameTime;
	PerformanceMonitorGroup m_chunkTerrainGeneration;
	PerformanceMonitorGroup m_chunkMeshGeneration;

public:
	GamePerformanceCounter();

	CUBIX_GET_R_CR( m_frameTime, FrameTimeCounter );
	CUBIX_GET_R_CR( m_chunkTerrainGeneration, TerrainGenCounter );
	CUBIX_GET_R_CR( m_chunkMeshGeneration, ChunkMeshCounter );

	void visualize();
};

} // namespace Game

#endif
