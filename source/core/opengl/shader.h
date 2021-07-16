#ifndef CUBIX_CORE_SHADER_H
#define CUBIX_CORE_SHADER_H

#include <string>
#include <vector>

#include <core/util/nocopy.h>

namespace Cubix
{
namespace Core
{
namespace GL
{

class Shader : public NoCopy
{
public:
	enum class Type : unsigned int
	{
		VERTEX_SHADER	= 0x8B31,
		FRAGMENT_SHADER = 0x8B30,
		GEOMETRY_SHADER = 0x8DD9
	};

private:
	unsigned int m_shaderID;
	std::string m_error;

public:
	Shader() = default;
	~Shader();

	bool compile( const std::string& source, const Type& type );
	bool isCompiled() const;
	void clear();
	unsigned int getID() const;
	const std::string& getError() const;
};

class Program : public NoCopy
{
private:
	unsigned int m_programID;
	std::string m_error;

	bool link( const std::vector< const Shader* >& shaders );

public:
	Program() = default;
	~Program();

	bool link( const Shader& vertexShader,
			   const Shader& fragmentShader,
			   const Shader& geometryShader );

	bool isLinked();
	void clear();
	const std::string& getError() const;
};

} // namespace GL
} // namespace Core
} // namespace Cubix

#endif // CUBIX_CORE_SHADER_H
