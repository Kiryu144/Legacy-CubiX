/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WINDOW_H
#define CUBIX_WINDOW_H

#include "core/cubix_macro.h"
#include "core/io/user_input_handler.h"

#include <memory>
#include <string>
#include <vector>

#include <glm/vec2.hpp>

struct GLFWwindow;

namespace Core
{

class Window
{

private:
	GLFWwindow* m_window{ nullptr };
	GLFWwindow* m_parent{ nullptr };

	std::unique_ptr< UserInputHandler > m_userInputHandler;

	void setupGLFW();
	void setupOpenGL();
	void setupImGui();

	bool m_vsync;
	std::string m_windowTitle;

public:
	Window( int width, int height, const std::string& title, GLFWwindow* parent = nullptr );
	Window( const Window& other ) = delete;
	~Window();
	Window& operator=( Window& other ) = delete;

	CUBIX_GET_V( m_vsync, VSync );
	CUBIX_GET_R_CR( m_userInputHandler, InputHandler );
	CUBIX_GET_CR( m_windowTitle, Title );

	static void Update();

	bool shouldClose() const;
	void swap();

	void setVSync( bool enable );

	void setTitle( const std::string& title );

	const glm::ivec2& getSize() const;
	void setSize( const glm::ivec2& size );
};

struct EventWindowResize
{
	unsigned int w, h;
};

} // namespace Core

#endif
