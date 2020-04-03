/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_SHADER_PROGRAM_H
#define CUBIX_SHADER_PROGRAM_H

#include "core/cubix_macro.h"
#include "core/logic/no_copy.h"
#include "core/opengl/opengl_helper.h"

#include <map>
#include <string>
#include <vector>

#include <GLM/mat4x4.hpp>
#include <glad/glad.h>

namespace Core
{

class ShaderProgram : Core::NoCopy
{
protected:
	typedef DestructibleGLuint< ProgramDeleter > Program;
	typedef DestructibleGLuint< ShaderDeleter > Shader;

public:
	typedef GLuint UniformLocation;

	enum ShaderType
	{
		VERTEX_SHADER	= GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER
	};

protected:
	std::map< GLenum, Shader > m_compiledShaders;
	Program m_program;

	std::map< std::string, UniformLocation > m_uniformLocations;

	void cacheUniformLocations();

public:
	ShaderProgram& compileShaderFromSource( const std::string& source,
											const ShaderType& shaderType );
	ShaderProgram& compileShaderFromFile( const std::string& file, const ShaderType& shaderType );

	bool link();
	void bind();

	int getUniformLocation( const std::string& uniformName ) const;
	ShaderProgram& setUniform( const std::string& uniform, float value );
	ShaderProgram& setUniform( const std::string& uniform, const glm::vec2& vec );
	ShaderProgram& setUniform( const std::string& uniform, const glm::vec3& vec );
	ShaderProgram& setUniform( const std::string& uniform, const glm::vec4& vec );
	ShaderProgram& setUniform( const std::string& uniform, const glm::mat4& mat );
};
} // namespace Core

#endif
