#include "shader.h"

#include <glad/glad.h>

namespace Cubix
{
namespace Core
{
namespace GL
{

Shader::~Shader()
{
	clear();
}

bool Shader::compile( const std::string& source, const Shader::Type& type )
{
	clear();
	m_shaderID = glCreateShader( static_cast< unsigned int >( type ) );

	const char* c_str = source.c_str();
	glShaderSource( m_shaderID, 1, &c_str, nullptr );
	glCompileShader( m_shaderID );

	// Check compilation status
	GLint status;
	glGetShaderiv( m_shaderID, GL_COMPILE_STATUS, &status );

	if( status != GL_TRUE )
	{
		// Error on compilation
		GLint logLength = 0;
		glGetShaderiv( m_shaderID, GL_INFO_LOG_LENGTH, &logLength );
		m_error.resize( logLength );
		glGetShaderInfoLog( m_shaderID, logLength, &logLength, &m_error.at( 0 ) );
		clear();
	}
	else
	{
		m_error = "";
	}

	return isCompiled();
}

void Shader::clear()
{
	if( m_shaderID == 0 )
	{
		return;
	}

	glDeleteShader( m_shaderID );
	m_shaderID = 0;
}

bool Shader::isCompiled() const
{
	return m_shaderID > 0 && m_error.empty();
}

unsigned int Shader::getID() const
{
	return m_shaderID;
}

const std::string& Shader::getError() const
{
	return m_error;
}

Program::~Program()
{
	clear();
}

bool Program::link( const std::vector< const Shader* >& shaders )
{
	clear();
	m_programID = glCreateProgram();

	for( auto shader : shaders )
	{
		if( shader->isCompiled() )
		{
			glAttachShader( m_programID, shader->getID() );
		}
	}

	glLinkProgram( m_programID );

	// Get link status
	GLint status;
	glGetProgramiv( m_programID, GL_LINK_STATUS, &status );

	if( status == GL_FALSE )
	{
		// Error on linking
		GLint logLength = 0;
		glGetProgramiv( m_programID, GL_INFO_LOG_LENGTH, &logLength );
		m_error.resize( logLength );
		glGetProgramInfoLog( m_programID, logLength, &logLength, &m_error.at( 0 ) );
		clear();
		return false;
	}
	else
	{
		m_error = "";
	}

	return true;
}

bool Program::link( const Shader& vertexShader,
					const Shader& fragmentShader,
					const Shader& geometryShader )
{
	std::vector< const Shader* > shaders;
	shaders.push_back( &vertexShader );
	shaders.push_back( &fragmentShader );
	shaders.push_back( &geometryShader );
	return link( shaders );
}

bool Program::isLinked()
{
	return m_programID > 0 && m_error.empty();
}

void Program::clear()
{
	if( m_programID == 0 )
	{
		return;
	}

	glDeleteProgram( m_programID );
	m_programID = 0;
}

const std::string& Program::getError() const
{
	return m_error;
}

} // namespace GL
} // namespace Core
} // namespace Cubix
