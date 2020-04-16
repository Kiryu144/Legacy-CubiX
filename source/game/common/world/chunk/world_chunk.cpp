/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk.h"

#include "game/common/world/world.h"

namespace Game
{

WorldChunk::WorldChunk( World& world, const glm::ivec3& chunkPosition )
	: EmptyWorldChunk( world, chunkPosition )
{
}

Voxel WorldChunk::getVoxelFromWorld( const glm::ivec3& position, const Voxel& _def ) const
{
	if( position.x < 0 || position.x >= GetSideLength() || position.y < 0
		|| position.y >= GetSideLength() || position.z < 0 || position.z >= GetSideLength() )
	{
		return _def;
		return m_world.getVoxel( m_chunkPosition * glm::ivec3( GetSize() )
									 + ( position % glm::ivec3( GetSize() ) ),
								 _def );
	}
	return getVoxel( position );
}

void WorldChunk::setVoxel( const glm::uvec3& position, const Voxel& voxel )
{
	auto& existingVoxel = m_data[ GetIndexForPosition( position ) ];
	if( existingVoxel.exists() != voxel.exists() )
	{
		m_voxelCount += voxel.exists() ? +1 : -1;
	}

	existingVoxel = voxel;
}

const Voxel& WorldChunk::getVoxel( const glm::uvec3& position ) const
{
	return m_data[ GetIndexForPosition( position ) ];
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

size_t WorldChunk::getVoxelCount()
{
	return m_voxelCount;
}

} // namespace Game