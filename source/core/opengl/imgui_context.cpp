/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "imgui_context.h"

#include "core/cubix_log.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace Core
{

ImguiContext::~ImguiContext()
{
	if( m_context != nullptr )
	{
		ImGui::DestroyContext( m_context );
		m_context = nullptr;
		Logger::Log( "Destroyed ImGui context" );
	}
}

void ImguiContext::init( GLFWwindow* window )
{
	m_context = ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL( window, true );
	ImGui_ImplOpenGL3_Init();

	Logger::Log( "Initialized ImGui context" );
}

void ImguiContext::startFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImguiContext::endFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
}

} // namespace Core