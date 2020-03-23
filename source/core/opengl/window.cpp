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

	if( glfwRawMouseMotionSupported() )
	{
		glfwSetInputMode( m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
		glfwSetInputMode( m_window, GLFW_STICKY_KEYS, GLFW_TRUE );
		// glfwSetInputMode( m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE );
	}
	else
	{
		Logger::Log(
			Logger::WARNING,
			"Raw Mouse Motion is not supported. This can result in glitchy mouse movement." );
	}

	glfwSetWindowSizeCallback( m_window, []( GLFWwindow* window, int w, int h ) {
		EventWindowResize resize{ static_cast< unsigned int >( w ),
								  static_cast< unsigned int >( h ) };
		Handler< EventWindowResize >::Fire( resize );
	} );

	glfwSetCursorPosCallback( m_window, []( GLFWwindow* window, double x, double y ) {
		EventMouseMove move{ x, y };
		Handler< EventMouseMove >::Fire( move );
	} );

	glfwSetKeyCallback( m_window,
						[]( GLFWwindow* window, int key, int scancode, int action, int mods ) {
							EventKeyPressed keyPressed{ key };
							Handler< EventKeyPressed >::Fire( keyPressed );
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
	return glfwWindowShouldClose( m_window );
}

void Window::swap()
{
	glfwSwapBuffers( m_window );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	static const std::vector< int > s_keys
		= { 32,	 39,  44,  45,	46,	 47,  48,  49,	50,	 51,  52,  53,	54,	 55,  56,
			57,	 59,  61,  65,	66,	 67,  68,  69,	70,	 71,  72,  73,	74,	 75,  76,
			77,	 78,  79,  80,	81,	 82,  83,  84,	85,	 86,  87,  88,	89,	 90,  91,
			92,	 93,  96,  161, 162, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265,
			266, 267, 268, 269, 280, 281, 282, 283, 284, 290, 291, 292, 293, 294, 295,
			296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310,
			311, 312, 313, 314, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330,
			331, 332, 333, 334, 335, 336, 340, 341, 342, 343, 344, 345, 346, 347, 348 };

	for( int key : s_keys )
	{
		if( glfwGetKey( m_window, key ) == GLFW_PRESS )
		{
			EventKeyPressed keyPressed{ key };
			Handler< EventKeyPressed >::Fire( keyPressed );
		}
	}
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