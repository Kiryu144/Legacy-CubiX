#ifndef CUBIX_CORE_BUFFER_H
#define CUBIX_CORE_BUFFER_H

#include <cstddef>

#include <core/opengl/helper.h>
#include <core/util/nocopy.h>

namespace Cubix
{
namespace Core
{
namespace GL
{

/// Represents any buffer on the GPU. This is a class to handle memory management on the GPU, aswell
/// as cut down on unnecessary glBindBuffer calls by caching the current bufferID. This of course
/// implies that this class MUST be the only way to access buffers on the GPU given any context.
class Buffer : public NoCopy, public StateIDHolder
{

public:
	enum class Type : unsigned int
	{
		ARRAY_BUFFER			  = 0x8892,
		ATOMIC_COUNTER_BUFFER	  = 0x92C0,
		COPY_READ_BUFFER		  = 0x8F36,
		COPY_WRITE_BUFFER		  = 0x8F37,
		DISPATCH_INDIRECT_BUFFER  = 0x90EE,
		DRAW_INDIRECT_BUFFER	  = 0x8F3F,
		ELEMENT_ARRAY_BUFFER	  = 0x8893,
		PIXEL_PACK_BUFFER		  = 0x88EB,
		PIXEL_UNPACK_BUFFER		  = 0x88EC,
		QUERY_BUFFER			  = 0x9192,
		SHADER_STORAGE_BUFFER	  = 0x90D2,
		TEXTURE_BUFFER			  = 0x8C2A,
		TRANSFORM_FEEDBACK_BUFFER = 0x8C8E,
		UNIFORM_BUFFER			  = 0x8A11
	};

private:
	unsigned int m_bufferId;
	/// The amount of bytes currently on the GPU.
	size_t m_size{ 0 };
	/// The buffer type on the GPU. Only valid if m_bufferID > 0
	Type m_type;

public:
	/// This is the current bufferID state on the GPU. It is thread_local, as any given
	/// opengl context can only be on any given thread.
	/// Quote from the wiki:
	/// "The current context is a thread-local variable, so a single process can have several
	/// threads, each of which has its own current context. However, a single context cannot be
	/// current in multiple threads at the same time."
	thread_local static BindableStateID bindableStateId;

	Buffer() = default;
	~Buffer();

	/// Uploads any arbitrary data to the GPU. Any already existing data on this buffer object
	/// will be overwritten.
	/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml
	///
	/// @param data Pointer to the first byte of the tightly-packed data array.
	/// @param size Size in bytes of the given data array. Size must be greater than 0.
	/// @param type Which buffer to use.
	void set( const void* data, const size_t& size, const Type& type );

	/// Uploads any arbitrary data to the GL_ARRAY_BUFFER of the GPU. Any already existing data
	/// on this buffer object will be overwritten.
	/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml
	///
	/// @param data Pointer to the first byte of the tightly-packed data array.
	/// @param size Size in bytes of the given data array. Size must be greater than 0.
	void set( const void* data, const size_t& size );

	/// Binds the current buffer. Current buffer must be valid.
	/// @see containsData()
	void bind() const;

	/// Removes any data from the GPU if applicable.
	void clear();

	/// @return Returns true if data is present on the GPU. This check just checks the internal
	/// bufferID. Any outside modification may not be detected.
	bool containsData() const;

	/// @return Returns the amount of bytes present in this buffer.
	size_t size() const;

	unsigned int getStateID() const override;
	unsigned int getTypeID() const override;
};

} // namespace GL
} // namespace Core
} // namespace Cubix

#endif
