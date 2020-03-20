/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WINDOW_H
#define CUBIX_WINDOW_H

#include <string>

// Forward declaration
struct GLFWwindow;

namespace Core
{

class Window
{
private:
	GLFWwindow* m_window{ nullptr };
	GLFWwindow* m_parent{ nullptr };

public:
	Window( int width, int height, const std::string& title, GLFWwindow* parent = nullptr );
	Window( const Window& other ) = delete;
	~Window();

	Window& operator=( Window& other ) = delete;

	static void Update();

	bool shouldClose() const;
	void swap();
};

} // namespace Core

#endif
