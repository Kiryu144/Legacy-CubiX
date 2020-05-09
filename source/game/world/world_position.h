/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_POSITION_H
#define CUBIX_WORLD_POSITION_H

#include <functional>

// clang-format off
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
// clang-format on

namespace Game
{

struct WorldPosition;

struct ChunkPosition : public glm::ivec2
{
	ChunkPosition( int x = 0, int y = 0 ) : glm::ivec2( x, y ) {}
	ChunkPosition( const glm::ivec2& vec ) : glm::ivec2( vec ) {}

	/// \return Returns the position of the chunk in the world
	WorldPosition toWorldPosition() const;
};

struct WorldPosition : public glm::ivec3
{
	WorldPosition( int x = 0, int y = 0, int z = 0 ) : glm::ivec3( x, y, z ) {}
	WorldPosition( const glm::ivec3& vec ) : glm::ivec3( vec ) {}

	/// \return Returns the chunkposition of the current worldposition
	ChunkPosition toChunkPosition() const;

	/// \return Returns the offset inside the chunk. This value is always inside the x,z chunk
	/// boundaries.
	glm::ivec3 toInnerChunkOffset() const;

	/// \param chunkPosition The known chunk position of the current worldposition
	/// \return Returns the offset inside the chunk. This value is always inside the x,z chunk
	/// boundaries
	glm::ivec3 toInnerChunkOffset( const ChunkPosition& chunkPosition ) const;

	/// \return Returns the 2d representation of the current worldposition
	glm::ivec2 toLayerPosition() const;
};

} // namespace Game

namespace std
{
template<>
struct hash< Game::ChunkPosition > : public std::hash< glm::ivec2 >
{
};
template<>
struct hash< Game::WorldPosition > : public std::hash< glm::ivec3 >
{
};
} // namespace std

#endif
