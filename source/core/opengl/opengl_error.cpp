/*
 * Copyright (c) 2020 David Klostermann.
 */

#include <glad/glad.h>

#include "core/cubix_log.h"

void __M_gl_clear_error()
{
	glGetError();
}

void __M_gl_log_error( const char* expr )
{
	if( GLenum error = glGetError() )
	{
		std::string errorStr;
		switch( error )
		{
		case GL_NO_ERROR:
			errorStr = "GL_NO_ERROR";
			break;
		case GL_INVALID_ENUM:
			errorStr = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			errorStr = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			errorStr = "GL_INVALID_OPERATION";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			errorStr = "GL_OUT_OF_MEMORY";
			break;
		case GL_STACK_UNDERFLOW:
			errorStr = "GL_STACK_UNDERFLOW";
			break;
		case GL_STACK_OVERFLOW:
			errorStr = "GL_STACK_OVERFLOW";
			break;
		default:
			errorStr = "UNKNOWN";
		}

		std::string msg
			= "OpenGL call '" + std::string( expr ) + "' caused an error state of " + errorStr;
		Core::Logger::Log( Core::Logger::WARNING, msg );
	}
}