/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "game_performance.h"

#include "defines.h"

#include <cmath>

#include <imgui/imgui.h>

namespace Game
{

GamePerformanceCounter::GamePerformanceCounter()
	: m_frameTime( "frametime" ),
	  m_chunkMeshGeneration( "chunk_mesh_generation" ),
	  m_chunkTerrainGeneration( "chunk_terrain_generation" )
{
}

void GamePerformanceCounter::visualize()
{
#if CUBIX_IMGUI
	ImGui::Text( "Frame Time: %f", m_frameTime.getTimeNeededInMilliseconds() );
	ImGui::Text( "Terrain Generation (worker): %f", m_chunkTerrainGeneration[0].getTimeNeededInMilliseconds() );
	ImGui::Text( "Mesh Generation (worker): %f", m_chunkMeshGeneration[0].getTimeNeededInMilliseconds());
#endif
}

} // namespace Game