#ifndef CUBIX_CORE_TEXTURE_H
#define CUBIX_CORE_TEXTURE_H

#include <vector>

#include <glm/vec2.hpp>
#include <core/opengl/helper.h>
#include <core/util/nocopy.h>

namespace Cubix
{
namespace Core
{
namespace GL
{

class TextureParameters
{
public:
	enum class Type : unsigned int
	{
		TEXTURE_1D					 = 0x0DE0,
		TEXTURE_1D_ARRAY			 = 0x8C18,
		TEXTURE_2D					 = 0x0DE1,
		TEXTURE_2D_ARRAY			 = 0x8C1A,
		TEXTURE_2D_MULTISAMPLE		 = 0x9100,
		TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9102,
		TEXTURE_3D					 = 0x806F,
		TEXTURE_CUBE_MAP			 = 0x8513,
		TEXTURE_CUBE_MAP_ARRAY		 = 0x9009,
		TEXTURE_RECTANGLE			 = 0x51F5
	};

	struct Parameter
	{
		unsigned int parameter;
		unsigned int value;
	};

	struct Parameters
	{
		Parameters() = delete;

		static const Parameter FILTER_NEAREST[ 2 ];
		static const Parameter FILTER_LINEAR[ 2 ];
		static const Parameter WRAP_REPEAT[ 2 ];
		static const Parameter WRAP_MIRRORED_REPEAT[ 2 ];
		static const Parameter WRAP_CLAMP_TO_EDGE[ 2 ];
		static const Parameter WRAP_CLAMP_TO_BORDER[ 2 ];
	};

private:
	Type m_type;
	std::vector< Parameter > m_parameters;

public:
	TextureParameters( const Type& mType = GL::TextureParameters::Type::TEXTURE_2D );
	void addParameter( const Parameter& parameter );
	void addParameter( const Parameter parameter[ 2 ] );

	Type getType() const
	{
		return m_type;
	}

	const std::vector< Parameter >& getParameters() const
	{
		return m_parameters;
	}
};

class Texture : public NoCopy, public StateIDHolder
{
public:
	enum class PixelFormat : unsigned int
	{
		RED				= 0x1903,
		RG				= 0x8227,
		RGB				= 0x1907,
		BGR				= 0x80E0,
		RGBA			= 0x1908,
		BGRA			= 0x80E0,
		RED_INTEGER		= 0x8D94,
		RG_INTEGER		= 0x8228,
		RGB_INTEGER		= 0x8D98,
		BGR_INTEGER		= 0x8D9A,
		RGBA_INTEGER	= 0x8D99,
		BGRA_INTEGER	= 0x8D9B,
		STENCIL_INDEX	= 0x1901,
		DEPTH_COMPONENT = 0x1902,
		DEPTH_STENCIL	= 0x84F9
	};

private:
	/// The texture ID as on the GPU.
	unsigned int m_textureID;

	/// The texture width/height on the GPU.
	glm::uvec2 m_size;

	/// The texture type on the GPU. Only valid if m_textureID > 0
	TextureParameters::Type m_type;

public:
	/// This is the current textureID state on the GPU. It is thread_local, as any given
	/// opengl context can only be on any given thread.
	/// Quote from the wiki:
	/// "The current context is a thread-local variable, so a single process can have several
	/// threads, each of which has its own current context. However, a single context cannot be
	/// current in multiple threads at the same time."
	thread_local static BindableStateID bindableStateId;

	Texture() = default;
	~Texture();

	/// Uploads any texture data to the GPU. Any already existing texture data on this texture
	/// object will be overwritten.
	///
	/// @param data Pointer to the first byte of the tightly-packed texture data array.
	/// @param size Size in pixels of the given data array. Area must be greater than 0.
	/// @param pixelFormat The format of the given data.
	void set( const unsigned char* data,
			  const glm::uvec2& size,
			  const PixelFormat& pixelFormat,
			  const TextureParameters& textureParameters );

	/// Binds the current texture. Current buffer must be valid.
	/// @see containsData()
	void bind() const;

	/// Removes any data from the GPU if applicable.
	void clear();

	/// @return Returns true if data is present on the GPU. This check just checks the internal
	/// textureID. Any outside modification may not be detected.
	bool containsData() const;

	/// @return Returns the size in pixels.
	const glm::uvec2& size() const;

	unsigned int getStateID() const override;
	unsigned int getTypeID() const override;
};

} // namespace GL
} // namespace Core
} // namespace Cubix

#endif // CUBIX_CORE_TEXTURE_H
