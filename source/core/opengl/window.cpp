/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "window.h"

#include "core/cubix_assert.h"
#include "core/cubix_log.h"
#include "core/event.h"

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
		glClearColor( 0.1, 0.1, 0.1, 1.0 );
		glEnable( GL_DEPTH_TEST );
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}

	glfwSetWindowSizeCallback( m_window, []( GLFWwindow* window, int w, int h ) {
		EventWindowResize resize{ static_cast< unsigned int >( w ),
								  static_cast< unsigned int >( h ) };
		Handler< EventWindowResize >::Fire( resize );
	} );
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

int Window::getWidth() const
{
	int w, h;
	glfwGetWindowSize( m_window, &w, &h );
	return w;
}
int Window::getHeight() const
{
	int w, h;
	glfwGetWindowSize( m_window, &w, &h );
	return h;
}

} // namespace Core