/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_H
#define CUBIX_WORLD_CHUNK_H

#include "core/cubix_assert.h"
#include "core/cubix_macro.h"

#include "game/world/chunk/world_chunk_layer.h"
#include "game/world/voxel/voxel.h"

#include <cmath>
#include <vector>

#include <glm/vec2.hpp>

namespace Game
{

class World;
class Entity;

class WorldChunk
{
public:
	static constexpr int GetSideLength()
	{
		return WorldChunkLayer::GetSideLength();
	}

	static constexpr int GetArea()
	{
		return WorldChunkLayer::GetArea();
	}

	static glm::uvec2 GetSize()
	{
		return WorldChunkLayer::GetSize();
	}

	static constexpr int GetMinYLevel()
	{
		return -1024;
	}

	static constexpr int GetMaxYLevel()
	{
		return 1024;
	}

	static glm::ivec2 ChunkPosFromWorldPos( const glm::ivec3& worldPosition )
	{
		return { std::floor( static_cast< float >( worldPosition.x ) / GetSideLength() ),
				 std::floor( static_cast< float >( worldPosition.z ) / GetSideLength() ) };
	}

	static glm::ivec3 WorldPosFromChunkPos( const glm::ivec2& chunkPosition )
	{
		return { chunkPosition.x * GetSideLength(), 0, chunkPosition.y * GetSideLength() };
	}

	static glm::ivec3 InsideChunkOffsetFromWorldPos( const glm::ivec3& worldPosition )
	{
		auto chunkPos = ChunkPosFromWorldPos( worldPosition );
		return { worldPosition.x - chunkPos.x * GetSideLength(),
				 worldPosition.y,
				 worldPosition.z - chunkPos.y * GetSideLength() };
	}

protected:
	World& m_world;
	glm::ivec2 m_chunkPosition;

	std::vector< std::shared_ptr< WorldChunkLayer > > m_data;
	glm::ivec2 m_heightBounds{ 0, 0 };

public:
	WorldChunk( World& world, const glm::ivec2& chunkPosition = glm::ivec2{ 0, 0 } );

	CUBIX_GET_CR( m_chunkPosition, ChunkPosition );
	CUBIX_GET_R_CR( m_world, World );
	CUBIX_GET_V( m_chunkPosition[ 0 ], LowestLayer );
	CUBIX_GET_V( m_chunkPosition[ 1 ], HighestLayer );

	std::shared_ptr< WorldChunkLayer >& getLayer( int y );
	const std::shared_ptr< WorldChunkLayer >& getLayer( int y ) const;
	std::shared_ptr< WorldChunkLayer >& getOrCreateLayer( int y );

	virtual void setVoxel( const glm::uvec3& position, const Voxel& voxel );
	Voxel getVoxel( const glm::uvec3& position ) const;
};

} // namespace Game

#endif
