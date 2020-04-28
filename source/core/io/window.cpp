/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "window.h"

#include "core/cubix_assert.h"
#include "core/event.h"
#include "core/opengl/imgui_context.h"
#include "core/opengl/opengl_context.h"

#include <glfw/glfw3.h>

namespace Core
{

Window::Window( int width, int height, const std::string& title, GLFWwindow* parent )
{
	cubix_assert( width > 0 && height > 0, "Invalid window size" );
	cubix_log_or_assert( glfwInit(), "Initialized GLFW3", "glfwInit() failed" );

	m_window	  = glfwCreateWindow( width, height, title.c_str(), nullptr, parent );
	m_windowTitle = title;

	cubix_log_or_assert( m_window, "Created window", "glfwCreateWindow() failed" );
	m_parent = parent;

	m_userInputHandler.reset( new UserInputHandler( m_window ) );

	glfwWindowHint( GLFW_DOUBLEBUFFER, true );
	glfwWindowHint( GLFW_SAMPLES, 2 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );

	glfwSetInputMode( m_window, GLFW_STICKY_KEYS, GLFW_TRUE );
	glfwMakeContextCurrent( m_window );

	Core::OpenGLContext::Get().init( ( GLADloadproc )glfwGetProcAddress );

#if CUBIX_IMGUI
	Core::ImguiContext::Get().init( m_window );
#endif

	glfwSetWindowSizeCallback( m_window, []( GLFWwindow* window, int w, int h ) {
		EventWindowResize resize{ static_cast< unsigned int >( w ),
								  static_cast< unsigned int >( h ) };
		Handler< EventWindowResize >::Fire( resize );
	} );

	glfwSetDropCallback( m_window, []( GLFWwindow* window, int count, const char** paths ) {
		EventWindowFileDrop fileDrop{ std::string( paths[ 0 ] ) };
		Handler< EventWindowFileDrop >::Fire( fileDrop );
	} );

	EventWindowResize resize{ static_cast< unsigned int >( width ),
							  static_cast< unsigned int >( height ) };
	Handler< EventWindowResize >::Fire( resize );
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
	return static_cast< bool >( glfwWindowShouldClose( m_window ) );
}

void Window::swap()
{
#if CUBIX_IMGUI
	static bool firstFrame = true;
	if( !firstFrame )
	{
		ImguiContext::Get().endFrame();
	}
	firstFrame = false;
#endif

	glfwSwapBuffers( m_window );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	m_userInputHandler->update();

#if CUBIX_IMGUI
	ImguiContext::Get().startFrame();
#endif
}

const glm::ivec2& Window::getSize() const
{
	static glm::ivec2 size;
	glfwGetWindowSize( m_window, &size.x, &size.y );
	return size;
}

void Window::setSize( const glm::ivec2& size )
{
	glfwSetWindowSize( m_window, size.x, size.y );
}

void Window::setTitle( const std::string& title )
{
	glfwSetWindowTitle( m_window, title.c_str() );
}

void Window::setVSync( bool enable )
{
	glfwSwapInterval( enable );
}

void Window::setMsaaSamples( int samples )
{
	glfwWindowHint( GLFW_SAMPLES, samples );
	m_msaaLevels = samples;
}

int Window::getMsaaSamples() const
{
	return m_msaaLevels;
}

} // namespace Core