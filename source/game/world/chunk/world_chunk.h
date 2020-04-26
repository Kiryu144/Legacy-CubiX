/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_H
#define CUBIX_WORLD_CHUNK_H

#include "core/cubix_assert.h"
#include "core/cubix_macro.h"

#include "game/world/voxel/voxel.h"

#include <cmath>
#include <vector>

namespace Game
{

class World;
class Entity;

class WorldChunk
{
public:
	static constexpr int GetSideLength()
	{
		return 32;
	}

	static constexpr int GetArea()
	{
		return GetSideLength() * GetSideLength();
	}

	static constexpr int GetVolume()
	{
		return GetSideLength() * GetSideLength() * GetSideLength();
	}

	static glm::uvec3 GetSize()
	{
		return glm::uvec3{ GetSideLength() };
	}

	static unsigned int GetIndexForPosition( const glm::uvec3& position )
	{
		// optimize: Evaluate creating a lookup table for the positions
		cubix_assert( position.x < GetSideLength() && position.y < GetSideLength()
						  && position.z < GetSideLength(),
					  "Out of range" );
		return ( position.z * GetArea() ) + ( position.y * GetSideLength() ) + position.x;
	}

	static glm::uvec3 GetPositionForIndex( unsigned int index )
	{
		// OPT: Evaluate creating a lookup table for the indicies
		unsigned int z = index / GetArea();
		index -= ( z * GetArea() );
		unsigned int y = index / GetSideLength();
		unsigned int x = index % GetSideLength();
		return { x, y, z };
	}

	static glm::ivec3 ChunkPosFromWorldPos( const glm::ivec3& worldPosition )
	{
		return { std::floor( static_cast< float >( worldPosition.x ) / GetSideLength() ),
				 std::floor( static_cast< float >( worldPosition.y ) / GetSideLength() ),
				 std::floor( static_cast< float >( worldPosition.z ) / GetSideLength() ) };
	}

	static glm::ivec3 WorldPosFromChunkPos( const glm::ivec3& chunkPosition )
	{
		return chunkPosition * glm::ivec3( GetSize() );
	}

protected:
	World& m_world;
	glm::ivec3 m_chunkPosition;

	std::vector< Voxel > m_data;
	size_t m_voxelCount{ 0 };

public:
	WorldChunk( World& world, const glm::ivec3& chunkPosition = glm::ivec3{ 0, 0, 0 } );

	CUBIX_GET_CR( m_chunkPosition, ChunkPosition );
	CUBIX_GET_R_CR( m_world, World );

	void initializeData();
	bool isInitialized() const;

	virtual void setVoxel( const glm::uvec3& position, const Voxel& voxel );
	const Voxel& getVoxel( const glm::uvec3& position ) const;

	size_t getVoxelCount() const;
};

} // namespace Game

#endif
