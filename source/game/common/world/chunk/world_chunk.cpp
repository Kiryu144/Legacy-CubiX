/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk.h"

#include "game/common/world/world.h"

namespace Game
{

WorldChunk::WorldChunk( World& world, const glm::ivec3& chunkPosition )
	: m_chunkPosition( chunkPosition ), m_world( world )
{
}

Voxel WorldChunk::getVoxelFromWorld( const glm::ivec3& position, const Voxel& _def ) const
{
	if( position.x < 0 || position.x >= GetSideLength() || position.y < 0
		|| position.y >= GetSideLength() || position.z < 0 || position.z >= GetSideLength() )
	{
		return m_world.getVoxel( m_chunkPosition * glm::ivec3( GetSize() )
									 + ( position % glm::ivec3( GetSize() ) ),
								 _def );
	}
	return getVoxel( position );
}

void WorldChunk::setVoxel( const glm::uvec3& position, const Voxel& voxel )
{
	m_data[ GetIndexForPosition( position ) ] = voxel;
}

const Voxel& WorldChunk::getVoxel( const glm::uvec3& position ) const
{
	return m_data[ GetIndexForPosition( position ) ];
}

World& WorldChunk::getWorld() const
{
	return m_world;
}

const glm::ivec3& WorldChunk::getChunkPosition() const
{
	return m_chunkPosition;
}

bool WorldChunk::isPopulated() const
{
	return m_isPopulated;
}

bool WorldChunk::isGenerated() const
{
	return m_isGenerated;
}

void WorldChunk::setPopulated()
{
	m_isPopulated = true;
}

void WorldChunk::setGenerated()
{
	m_isGenerated = true;
}

void WorldChunk::setMillisecondsNotSeen( int ms )
{
	m_millisecondsNotSeen = ms;
}

int WorldChunk::getMillisecondsNotSeen()
{
	return m_millisecondsNotSeen;
}

} // namespace Game