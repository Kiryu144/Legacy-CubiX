/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_LAYER_H
#define CUBIX_WORLD_CHUNK_LAYER_H

#include "defines.h"

#include "core/cubix_assert.h"
#include "core/cubix_macro.h"

#include "game/world/voxel/voxel.h"

#include <array>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Game
{

class WorldChunk;

class WorldChunkLayer
{
public:
	static constexpr int GetSideLength()
	{
		return CUBIX_CHUNK_SIZE;
	}

	static constexpr int GetArea()
	{
		return GetSideLength() * GetSideLength();
	}

	static glm::uvec2 GetSize()
	{
		return glm::uvec2{ GetSideLength() };
	}

	static size_t GetIndexForLayer( const glm::uvec2& position )
	{
		cubix_assert( position.x < GetSideLength() && position.y < GetSideLength(),
					  "Out of range" );
		return position.y * GetSideLength() + position.x;
	}

protected:
	WorldChunk& m_worldChunk;
	int m_yLevel;

	std::array< Voxel, CUBIX_CHUNK_SIZE * CUBIX_CHUNK_SIZE > m_data;

	size_t m_voxelCount{ 0 };

public:
	WorldChunkLayer( WorldChunk& worldChunk, int yLevel );

	CUBIX_GET_R_CR( m_worldChunk, WorldChunk );
	CUBIX_GET_R_CR( m_yLevel, Y );
	CUBIX_GET_R_CR( m_voxelCount, VoxelCount );

	void setVoxel( size_t index, Voxel voxel );
	Voxel getVoxel( size_t index ) const;

	void setVoxel( const glm::ivec2& position, Voxel voxel );
	Voxel getVoxel( const glm::ivec2& position ) const;
};

} // namespace Game

#endif
