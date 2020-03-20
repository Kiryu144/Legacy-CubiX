/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "window.h"

#include "core/cubix_assert.h"
#include "core/cubix_log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core
{

Window::Window( int width, int height, const std::string& title, GLFWwindow* parent )
{
	cubix_assert( width > 0 && height > 0, "Invalid window size" );
	cubix_log_or_assert( glfwInit(), "Initialized GLFW", "Unable to initialize GLFW" );
	m_window = glfwCreateWindow( width, height, title.c_str(), nullptr, parent );
	cubix_log_or_assert(
		m_window, "Created window '" + title + "'", "Unable to create GLFW Window" );
	m_parent = parent;

	glfwSwapInterval( 0 ); // Disable VSync
	if( !parent )
	{
		glfwWindowHint( GLFW_DOUBLEBUFFER, true );
		glfwWindowHint( GLFW_SAMPLES, 2 );
		glfwMakeContextCurrent( m_window );

		gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress );
		cubix_log_or_assert( gladLoadGL(),
							 "Created opengl context for window '" + title + "'",
							 "Unable to load opengl" );

		glViewport( 0, 0, width, height );
	}
}

Window::~Window()
{
	glfwDestroyWindow( m_window );
}

void Window::Update()
{
	glfwPollEvents();
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose( m_window );
}

void Window::swap()
{
	glfwSwapBuffers( m_window );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

} // namespace Core