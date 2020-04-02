/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "window.h"

#include "core/cubix_assert.h"
#include "core/event.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
// clang-format on

namespace Core
{

Window::Window( int width, int height, const std::string& title, GLFWwindow* parent )
{
	cubix_assert( width > 0 && height > 0, "Invalid window size" );
	cubix_log_or_assert( glfwInit(), "Initialized GLFW3", "Unable to initialize GLFW" );
	m_window	  = glfwCreateWindow( width, height, title.c_str(), nullptr, parent );
	m_windowTitle = title;
	cubix_log_or_assert( m_window, "Created window", "Unable to create GLFW Window" );
	m_parent = parent;

	m_userInputHandler.reset( new UserInputHandler( m_window ) );

	setupGLFW();
	setupOpenGL();

#if CUBIX_IMGUI
	setupImGui();
#endif

	glfwSetWindowSizeCallback( m_window, []( GLFWwindow* window, int w, int h ) {
		EventWindowResize resize{ static_cast< unsigned int >( w ),
								  static_cast< unsigned int >( h ) };
		Handler< EventWindowResize >::Fire( resize );
	} );

	EventWindowResize resize{ static_cast< unsigned int >( width ),
							  static_cast< unsigned int >( height ) };
	Handler< EventWindowResize >::Fire( resize );

	setVSync( false );
}

void Window::setupGLFW()
{
	glfwWindowHint( GLFW_DOUBLEBUFFER, true );
	glfwWindowHint( GLFW_SAMPLES, 2 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );

	glfwSetInputMode( m_window, GLFW_STICKY_KEYS, GLFW_TRUE );
}

void Window::setupOpenGL()
{
	glfwMakeContextCurrent( m_window );
	gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress );

	cubix_log_or_assert( gladLoadGL(), "Initialized OpenGL", "Unable to load opengl" );

	auto size = getSize();
	glViewport( 0, 0, size.x, size.y );
	glClearColor( 179 / 255.0f, 210 / 255.0f, 238 / 255.0f, 1.0 );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void Window::setupImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	( void )io;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL( m_window, true );
	ImGui_ImplOpenGL3_Init( "#version 410" );

	Logger::Log( "Initialized ImGui" );
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
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
	}
	firstFrame = false;
#endif

	glfwSwapBuffers( m_window );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	m_userInputHandler->update();

#if CUBIX_IMGUI
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
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

} // namespace Core