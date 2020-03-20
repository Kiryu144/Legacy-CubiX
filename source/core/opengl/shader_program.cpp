/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "shader_program.h"

#include "core/opengl/openg_error.h"

#include <fstream>

namespace Core
{

ShaderProgram& ShaderProgram::compileShaderFromSource( const std::string& source,
													   const ShaderProgram::ShaderType& shaderType )
{
	gl_clear_error();
	GLuint shader	  = gl_log_error( glCreateShader( shaderType ) );
	const char* c_str = source.c_str();
	gl_log_error( glShaderSource( shader, 1, &c_str, nullptr ) );
	gl_log_error( glad_glCompileShader( shader ) );

	GLint status;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &status );

	if( status == GL_TRUE )
	{
		Logger::Log( "Compiled shader ID:" + std::to_string( shader ) );
		m_compiledShaders[ shaderType ] = shader;
	}
	else
	{
		Logger::Log( Logger::WARNING, "Error on compiling shader ID:" + std::to_string( shader ) );
		glDeleteShader( shader );
	}

	return *this;
}

ShaderProgram& ShaderProgram::compileShaderFromFile( const std::string& file,
													 const ShaderProgram::ShaderType& shaderType )
{
	std::ifstream f( file );
	if( f.fail() )
	{
		Logger::Log( Logger::WARNING, "Unable to open file " + file );
		return *this;
	}

	std::string src( ( std::istreambuf_iterator< char >( f ) ),
					 std::istreambuf_iterator< char >() );
	compileShaderFromSource( src, shaderType );

	return *this;
}

ShaderProgram& ShaderProgram::link()
{
	m_program = gl_log_error( glCreateProgram() );

	for( auto it : m_compiledShaders )
	{
		gl_log_error( glAttachShader( m_program, it.second ) );
	}

	gl_log_error( glLinkProgram( m_program ) );

	for( auto it : m_compiledShaders )
	{
		glDeleteShader( it.second );
	}

	GLint status;
	glGetProgramiv( m_program, GL_LINK_STATUS, &status );

	if( status == GL_TRUE )
	{
		Logger::Log( "Linked shader program ID:" + std::to_string( m_program ) );
	}
	else
	{
		Logger::Log( Logger::WARNING,
					 "Error on compiling shader program ID:" + std::to_string( m_program ) );
		glDeleteProgram( m_program );
		m_program = 0;
	}

	m_compiledShaders.clear();

	return *this;
}

} // namespace Core