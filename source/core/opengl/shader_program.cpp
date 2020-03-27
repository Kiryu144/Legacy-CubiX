/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "shader_program.h"

#include "core/cubix_log.h"
#include "core/opengl/openg_error.h"
#include "core/opengl/opengl_helper.h"

#include <fstream>

namespace Core
{

ShaderProgram::~ShaderProgram()
{
	if( m_program != 0 )
	{
		glDeleteProgram( m_program );
		m_program = 0;
	}
}

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
		m_compiledShaders[ shaderType ] = shader;
	}
	else
	{
		GLint logLength = 0;
		gl_log_error( glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLength ) );
		std::string log( logLength, 0 );
		gl_log_error( glGetShaderInfoLog( shader, logLength, &logLength, &log.at( 0 ) ) );

		Logger::Log( Logger::WARNING,
					 "Error on compiling " + Core::to_string( shaderType )
						 + " shader ID: " + std::to_string( shader ) + "\n" + log );

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

	if( status == GL_FALSE )
	{
		GLint logLength = 0;
		gl_log_error( glGetProgramiv( m_program, GL_INFO_LOG_LENGTH, &logLength ) );
		std::string log( logLength, 0 );
		gl_log_error( glGetProgramInfoLog( m_program, logLength, &logLength, &log.at( 0 ) ) );

		Logger::Log( Logger::WARNING,
					 "Error on linking shader program ID: " + std::to_string( m_program ) + "\n"
						 + log );

		glDeleteProgram( m_program );
		m_program = 0;
	}

	m_compiledShaders.clear();

	return *this;
}

ShaderProgram& ShaderProgram::bind()
{
	glUseProgram( m_program );
	return *this;
}

void ShaderProgram::bind() const
{
	glUseProgram( m_program );
}

int ShaderProgram::getUniformLocation( const std::string& uniformName ) const
{
	return gl_log_error( glGetUniformLocation( m_program, uniformName.c_str() ) );
}

ShaderProgram& ShaderProgram::setUniform( const std::string& uniform, float value )
{
	glUniform1f( getUniformLocation( uniform ), value );
	return *this;
}

ShaderProgram& ShaderProgram::setUniform( const std::string& uniform, const glm::vec2& vec )
{
	glUniform2f( getUniformLocation( uniform ), vec.x, vec.y );
	return *this;
}

ShaderProgram& ShaderProgram::setUniform( const std::string& uniform, const glm::vec3& vec )
{
	glUniform3f( getUniformLocation( uniform ), vec.x, vec.y, vec.z );
	return *this;
}

ShaderProgram& ShaderProgram::setUniform( const std::string& uniform, const glm::vec4& vec )
{
	glUniform4f( getUniformLocation( uniform ), vec.x, vec.y, vec.z, vec.w );
	return *this;
}

ShaderProgram& ShaderProgram::setUniform( const std::string& uniform, const glm::mat4& mat )
{
	glUniformMatrix4fv( getUniformLocation( uniform ), 1, GL_FALSE, &mat[ 0 ][ 0 ] );
	return *this;
}

} // namespace Core