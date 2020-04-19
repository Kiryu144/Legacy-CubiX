/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_IMGUI_CONTEXT_H
#define CUBIX_IMGUI_CONTEXT_H

#include "core/logic/singelton.h"

struct GLFWwindow;
struct ImGuiContext;

namespace Core
{

class ImguiContext : public Singelton< ImguiContext >
{
protected:
	ImGuiContext* m_context{ nullptr };

public:
	~ImguiContext();

	void init( GLFWwindow* window );
	void startFrame();
	void endFrame();
};

} // namespace Core

#endif
