/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_SHADER_PROGRAM_H
#define CUBIX_SHADER_PROGRAM_H

#include <string>
#include <map>
#include <glad/glad.h>
#include <GLM/mat4x4.hpp>

namespace Core
{

class ShaderProgram
{
private:
	std::map< GLenum, GLuint > m_compiledShaders;

protected:
	GLuint m_program;

public:
	enum ShaderType
	{
		VERTEX_SHADER	= GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER
	};

	ShaderProgram()								= default;
	ShaderProgram( const ShaderProgram& other ) = delete;
	~ShaderProgram();

	ShaderProgram& compileShaderFromSource( const std::string& source,
											const ShaderType& shaderType );
	ShaderProgram& compileShaderFromFile( const std::string& file, const ShaderType& shaderType );
	ShaderProgram& link();

	ShaderProgram& bind();
	void bind() const;

	int getUniformLocation( const std::string& uniformName ) const;
	ShaderProgram& setUniform( const std::string& uniform, float value );
	ShaderProgram& setUniform( const std::string& uniform, const glm::vec2& vec );
	ShaderProgram& setUniform( const std::string& uniform, const glm::vec3& vec );
	ShaderProgram& setUniform( const std::string& uniform, const glm::vec4& vec );
	ShaderProgram& setUniform( const std::string& uniform, const glm::mat4& mat );
};
} // namespace Core

#endif
