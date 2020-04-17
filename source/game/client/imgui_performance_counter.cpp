/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "imgui_performance_counter.h"

#include "defines.h"

#include <imgui/imgui.h>

namespace Game
{

void ImguiPerformanceCounter::draw()
{
#if CUBIX_IMGUI
	ImGui::Begin( "Timings" );

	std::string name{ "Frame Time: " + std::to_string( m_frameTime.getAverageMs() ) };
	ImGui::PlotLines( name.c_str(), m_frameTime.getValues(), m_frameTime.getSampleRate() );

	ImGui::End();
#endif
}

} // namespace Game