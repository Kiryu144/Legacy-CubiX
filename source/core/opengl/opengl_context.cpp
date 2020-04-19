/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "opengl_context.h"

#include "defines.h"

#include "core/cubix_assert.h"
#include "core/logic/string_cast.h"

namespace Core
{

OpenGLContext::~OpenGLContext()
{
	if( m_initialized )
	{
		Logger::Log( "Deleted OpenGL context for thread "
					 + Core::to_string( std::this_thread::get_id() ) );
	}
}

void OpenGLContext::init( GLADloadproc glaDloadproc )
{
	cubix_assert( !m_initialized, "OpenGL context is already initialized for thread" );

	cubix_assert( gladLoadGL(), "gladLoadGL() failed" );
	cubix_assert( gladLoadGLLoader( glaDloadproc ), "gladLoadGLLoader() failed" );

	glClearColor( 0.2f, 0.2f, 0.2f, 1.0 );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_BLEND );
	glEnable( GL_CULL_FACE );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

#ifdef CUBIX_GL_ERROR_CALLBACK
	glEnable( GL_DEBUG_OUTPUT );
	glDebugMessageCallback( _OnGlError, 0 );
#endif

	const char* glVersion{ reinterpret_cast< const char* >( glGetString( GL_VERSION ) ) };

	Logger::Log( "Created OpenGL " + std::string( glVersion ) + " context for thread "
				 + Core::to_string( std::this_thread::get_id() ) );
	m_initialized = true;
}

void _OnGlError( GLenum source,
				 GLenum type,
				 GLuint id,
				 GLenum severity,
				 GLsizei length,
				 const GLchar* message,
				 const void* userParam )
{
	if( type == GL_DEBUG_TYPE_ERROR )
	{
		Logger::Warn( "OpenGL Error: " + std::string( message ) );
	}
}

} // namespace Core