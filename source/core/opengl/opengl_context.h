/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_OPENGL_CONTEXT_H
#define CUBIX_OPENGL_CONTEXT_H

#include <glad/glad.h>

namespace Core
{

class OpenGLContext
{
protected:
	OpenGLContext() = default;
	~OpenGLContext();

	bool m_initialized{ false };

public:
	void init( GLADloadproc glaDloadproc );

	static OpenGLContext& Get()
	{
		thread_local static OpenGLContext glContext;
		return glContext;
	}
};

void _OnGlError( GLenum source,
				 GLenum type,
				 GLuint id,
				 GLenum severity,
				 GLsizei length,
				 const GLchar* message,
				 const void* userParam );

} // namespace Core

#endif
