/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_I_WORLD_CHUNK_H
#define CUBIX_I_WORLD_CHUNK_H

#include "core/cubix_assert.h"

#include "game/world/voxel/voxel.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

namespace Game
{

class World;

class IWorldChunk
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
		// OPT: Evaluate creating a lookup table for the positions
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
		return { std::floor( worldPosition.x / GetSideLength() ),
				 std::floor( worldPosition.y / GetSideLength() ),
				 std::floor( worldPosition.z / GetSideLength() ) };
	}

	static glm::ivec3 WorldPosFromChunkPos( const glm::ivec3& chunkPosition )
	{
		return chunkPosition * glm::ivec3( GetSize() );
	}

	virtual void setVoxel( const glm::uvec3& position, const Voxel& voxel ) = 0;
	virtual const Voxel& getVoxel( const glm::uvec3& position ) const		= 0;

	virtual World& getWorld() const										 = 0;
	virtual const glm::ivec3& getChunkPosition() const					 = 0;
	virtual Voxel getVoxelFromWorld( const glm::ivec3& position,
									 const Voxel& _def = Voxel() ) const = 0;

	virtual bool isPopulated() const = 0;
	virtual bool isGenerated() const = 0;

	virtual void setPopulated() = 0;
	virtual void setGenerated() = 0;

	virtual void setMillisecondsNotSeen( int ms ) = 0;
	virtual int getMillisecondsNotSeen()		  = 0;

	virtual size_t getVoxelCount() = 0;
};

} // namespace Game

#endif
