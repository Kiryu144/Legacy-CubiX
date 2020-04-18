/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "shader_program.h"

#include "core/cubix_assert.h"
#include "core/opengl/openg_error.h"

#include <fstream>

namespace Core
{

ShaderProgram::ShaderProgram( ShaderProgram&& other ) : m_program( std::move( other.m_program ) )
{
	m_compiledShaders.merge( other.m_compiledShaders );
	m_uniformLocations.merge( other.m_uniformLocations );
}

ShaderProgram& ShaderProgram::compileShaderFromSource( const std::string& source,
													   const ShaderProgram::ShaderType& shaderType )
{
	gl_clear_error();
	Shader shader{ glCreateShader( shaderType ) };
	const char* c_str = source.c_str();
	gl_log_error( glShaderSource( shader.getID(), 1, &c_str, nullptr ) );
	gl_log_error( glCompileShader( shader.getID() ) );

	// Check compilation status
	GLint status;
	glGetShaderiv( shader.getID(), GL_COMPILE_STATUS, &status );

	if( status == GL_TRUE )
	{
		// Compiled successfully
		m_compiledShaders.insert( { shaderType, std::move( shader ) } );
	}
	else
	{
		// Error on compilation
		GLint logLength = 0;
		gl_log_error( glGetShaderiv( shader.getID(), GL_INFO_LOG_LENGTH, &logLength ) );
		std::string log( logLength, 0 );
		gl_log_error( glGetShaderInfoLog( shader.getID(), logLength, &logLength, &log.at( 0 ) ) );
		Logger::Log( Logger::WARNING,
					 "Error on compiling " + Core::to_string( shaderType )
						 + " shader ID: " + std::to_string( shader.getID() ) + "\n" + log );
	}

	return *this;
}

ShaderProgram& ShaderProgram::compileShaderFromFile( const std::string& file,
													 const ShaderProgram::ShaderType& shaderType )
{
	std::ifstream f( file );
	if( f.fail() )
	{
		Logger::Log( Logger::WARNING, "Unable to open shader file " + file );
		return *this;
	}

	std::string src( ( std::istreambuf_iterator< char >( f ) ),
					 std::istreambuf_iterator< char >() );
	compileShaderFromSource( src, shaderType );
	return *this;
}

bool ShaderProgram::link()
{
	m_program = std::move( Program( glCreateProgram() ) );

	// Attach all compiled shaders
	for( auto& it : m_compiledShaders )
	{
		gl_log_error( glAttachShader( m_program.getID(), it.second.getID() ) );
	}

	gl_log_error( glLinkProgram( m_program.getID() ) );

	// Get link status
	GLint status;
	glGetProgramiv( m_program.getID(), GL_LINK_STATUS, &status );

	if( status == GL_FALSE )
	{
		// Error on linking
		GLint logLength = 0;
		gl_log_error( glGetProgramiv( m_program.getID(), GL_INFO_LOG_LENGTH, &logLength ) );
		std::string log( logLength, 0 );
		gl_log_error(
			glGetProgramInfoLog( m_program.getID(), logLength, &logLength, &log.at( 0 ) ) );

		Logger::Log( Logger::WARNING,
					 "Error on linking shader program ID: " + std::to_string( m_program.getID() )
						 + "\n" + log );
		return false;
	}

	m_compiledShaders.clear();
	cacheUniformLocations();
	return true;
}

void ShaderProgram::bind()
{
	glUseProgram( m_program.getID() );
}

void ShaderProgram::cacheUniformLocations()
{
	if( !m_program.getID() )
	{
		return;
	}

	int count;
	glGetProgramiv( m_program.getID(), GL_ACTIVE_UNIFORMS, &count );

	GLint size;
	GLuint type;
	const GLsizei bufSize = 32;
	GLchar name[ bufSize ];
	GLsizei length;

	for( int i = 0; i < count; ++i )
	{
		glGetActiveUniform(
			m_program.getID(), static_cast< GLuint >( i ), bufSize, &length, &size, &type, name );
		m_uniformLocations[ std::string( name ) ] = static_cast< UniformLocation >( i );
	}

	m_projectionUniform = getUniformLocation( "u_projection" );
	m_viewUniform		= getUniformLocation( "u_view" );
	m_transformUniform	= getUniformLocation( "u_transformation" );
}

int ShaderProgram::getUniformLocation( const std::string& uniformName ) const
{
	auto it = m_uniformLocations.find( uniformName );
	if( it == m_uniformLocations.end() )
	{
		Logger::Warn( "Unknown uniform " + uniformName );
		return -1;
	}
	return it->second;
}

ShaderProgram& ShaderProgram::setUniform( int uniformLocation, float value )
{
	glUniform1f( uniformLocation, value );
	return *this;
}

ShaderProgram& ShaderProgram::setUniform( int uniformLocation, const glm::vec2& vec )
{
	glUniform2f( uniformLocation, vec.x, vec.y );
	return *this;
}

ShaderProgram& ShaderProgram::setUniform( int uniformLocation, const glm::vec3& vec )
{
	glUniform3f( uniformLocation, vec.x, vec.y, vec.z );
	return *this;
}

ShaderProgram& ShaderProgram::setUniform( int uniformLocation, const glm::vec4& vec )
{
	glUniform4f( uniformLocation, vec.x, vec.y, vec.z, vec.w );
	return *this;
}

ShaderProgram& ShaderProgram::setUniform( int uniformLocation, const glm::mat4& mat )
{
	glUniformMatrix4fv( uniformLocation, 1, GL_FALSE, &mat[ 0 ][ 0 ] );
	return *this;
}

} // namespace Core