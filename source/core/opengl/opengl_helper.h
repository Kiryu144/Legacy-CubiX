/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_OPENGL_HELPER_H
#define CUBIX_OPENGL_HELPER_H

#include "core/cubix_macro.h"
#include "core/logic/no_copy.h"

#include <memory>
#include <string>

#include <glad/glad.h>

namespace Core
{

const std::string& to_string( GLenum e );

void ShaderDeleter( GLuint shader );
void ProgramDeleter( GLuint program );

template< decltype( ShaderDeleter ) Deleter >
class DestructibleGLuint : Core::NoCopy
{
protected:
	GLuint m_id{ 0 };

public:
	DestructibleGLuint( GLuint id = 0 ) : m_id( id ) {}
	DestructibleGLuint( DestructibleGLuint&& other )
	{
		this->m_id = other.m_id;
		other.m_id = 0;
	}

	DestructibleGLuint& operator=( DestructibleGLuint&& other )
	{
		this->m_id = other.m_id;
		other.m_id = 0;
		return *this;
	}

	~DestructibleGLuint()
	{
		Deleter( m_id );
	}

	CUBIX_GET_SET_CR_CR( m_id, ID );
};

} // namespace Core

#endif // CUBIX_OPENGL_HELPER_H
