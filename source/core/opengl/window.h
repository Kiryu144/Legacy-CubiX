#ifndef CUBIX_CORE_WINDOW_H
#define CUBIX_CORE_WINDOW_H

#include <string>

#include <glm/vec2.hpp>

struct GLFWwindow;

namespace Cubix
{
namespace Core
{

class Window
{
public:
	static int FLAG_RESIZEABLE;

private:
	GLFWwindow* m_glfwWindow;

public:
	Window( const std::string& title, const glm::ivec2& size, int flags, Window* parent = nullptr );

	glm::ivec2 getSize() const;
	void setSize( const glm::ivec2& size );
	void setTitle( const std::string& title );
	bool shouldClose() const;
	void update() const;
	void close() const;
};

} // namespace DrawIO
}

#endif