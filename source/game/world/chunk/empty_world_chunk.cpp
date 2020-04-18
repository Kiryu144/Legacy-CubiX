/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "empty_world_chunk.h"

#include "game/world/voxel/voxel.h"

namespace Game
{

EmptyWorldChunk::EmptyWorldChunk( World& world, const glm::ivec3& chunkPosition )
	: m_world( world ), m_chunkPosition( chunkPosition )
{
}

void EmptyWorldChunk::setVoxel( const glm::uvec3& position, const Voxel& voxel ) {}

const Voxel& EmptyWorldChunk::getVoxel( const glm::uvec3& position ) const
{
	static const Voxel noVoxel;
	return noVoxel;
}

World& EmptyWorldChunk::getWorld() const
{
	return m_world;
}

const glm::ivec3& EmptyWorldChunk::getChunkPosition() const
{
	return m_chunkPosition;
}

Voxel EmptyWorldChunk::getVoxelFromWorld( const glm::ivec3& position, const Voxel& _def ) const
{
	return _def;
}

bool EmptyWorldChunk::isPopulated() const
{
	return true;
}

bool EmptyWorldChunk::isGenerated() const
{
	return true;
}

void EmptyWorldChunk::setMillisecondsNotSeen( int ms )
{
	m_millisecondsNotSeen = ms;
}

int EmptyWorldChunk::getMillisecondsNotSeen()
{
	return m_millisecondsNotSeen;
}

size_t EmptyWorldChunk::getVoxelCount()
{
	return 0;
}

} // namespace Game