#include "window.h"

#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Cubix
{
namespace Core
{
int Window::FLAG_RESIZEABLE = 1 << 0;

Window::Window( const std::string& title, const glm::ivec2& size, int flags, Window* parent )
{
	assert( glfwInit() );

	// Use opengl 4.1
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
	glfwWindowHint( GLFW_RESIZABLE, flags & FLAG_RESIZEABLE );

	// Create window
	m_glfwWindow = glfwCreateWindow(
		size.x, size.y, title.c_str(), nullptr, parent ? parent->m_glfwWindow : nullptr );

	// Error on window creation
	if( !m_glfwWindow )
	{
		std::cerr << "glfwCreateWindow failed with error: " << glfwGetError( nullptr ) << std::endl;
		assert( m_glfwWindow );
	}

	glfwMakeContextCurrent( m_glfwWindow );

	assert( gladLoadGL() );

	glfwSetWindowSizeCallback(
		m_glfwWindow, []( GLFWwindow* window, int w, int h ) { glViewport( 0, 0, w, h ); } );
}

glm::ivec2 Window::getSize() const
{
	glm::ivec2 size;
	glfwGetWindowSize( m_glfwWindow, &size.x, &size.y );
	return size;
}

void Window::setSize( const glm::ivec2& size )
{
	glfwSetWindowSize( m_glfwWindow, size.x, size.y );
}

void Window::setTitle( const std::string& title )
{
	glfwSetWindowTitle( m_glfwWindow, title.c_str() );
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose( m_glfwWindow );
}

void Window::update() const
{
	glfwPollEvents();
	glfwSwapBuffers( m_glfwWindow );
}

void Window::close() const
{
	glfwSetWindowShouldClose( m_glfwWindow, GLFW_TRUE );
}

} // namespace Core
} // namespace Cubix