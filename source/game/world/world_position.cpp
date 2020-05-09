/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_position.h"

#include "defines.h"

namespace Game
{

WorldPosition ChunkPosition::toWorldPosition() const
{
	WorldPosition worldPosition;
	worldPosition.x = x * CUBIX_CHUNK_SIZE;
	worldPosition.z = y * CUBIX_CHUNK_SIZE;
	return worldPosition;
}

WorldPosition ChunkPosition::toWorldPosition( const WorldPosition& offset ) const
{
	WorldPosition worldPosition;
	worldPosition.x = x * CUBIX_CHUNK_SIZE + offset.x;
	worldPosition.y = offset.y;
	worldPosition.z = y * CUBIX_CHUNK_SIZE + offset.z;
	return worldPosition;
}

ChunkPosition WorldPosition::toChunkPosition() const
{
	ChunkPosition chunkPosition;
	chunkPosition.x
		= static_cast< int >( std::floor( static_cast< float >( x ) / CUBIX_CHUNK_SIZE ) );
	chunkPosition.y
		= static_cast< int >( std::floor( static_cast< float >( z ) / CUBIX_CHUNK_SIZE ) );
	return chunkPosition;
}

glm::ivec3 WorldPosition::toInnerChunkOffset() const
{
	ChunkPosition chunkPosition{ toChunkPosition() };
	return toInnerChunkOffset( chunkPosition );
}

glm::ivec3 WorldPosition::toInnerChunkOffset( const ChunkPosition& chunkPosition ) const
{
	glm::ivec3 position;
	position.x = x - ( CUBIX_CHUNK_SIZE * chunkPosition.x );
	position.y = y;
	position.z = z - ( CUBIX_CHUNK_SIZE * chunkPosition.y );
	return position;
}

glm::ivec2 WorldPosition::toLayerPosition() const
{
	return glm::ivec2{ x, z };
}

} // namespace Game