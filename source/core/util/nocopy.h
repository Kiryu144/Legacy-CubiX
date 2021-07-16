#ifndef CUBIX_CORE_NOCOPY_H
#define CUBIX_CORE_NOCOPY_H

namespace Cubix
{
namespace Core
{

/// This is a simple utility class, which when inherited from, deletes the copy & move constructor,
/// as well as the assignment operator.
class NoCopy
{
public:
	NoCopy() = default;

	NoCopy( const NoCopy& other ) = delete;

	NoCopy( const NoCopy&& other ) = delete;

	NoCopy& operator=( const NoCopy& other ) = delete;
};

} // namespace Core
} // namespace Cubix

#endif
