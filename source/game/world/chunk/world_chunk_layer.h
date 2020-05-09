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
	static size_t GetIndexForLayer( const glm::uvec2& position )
	{
		cubix_assert( position.x < CUBIX_CHUNK_SIZE && position.y < CUBIX_CHUNK_SIZE,
					  "Out of range" );
		return position.y * CUBIX_CHUNK_SIZE + position.x;
	}

protected:
	WorldChunk& m_worldChunk;
	int m_yLevel;

	WorldChunkLayer* m_nextLayer{ nullptr };
	WorldChunkLayer* m_prevLayer{ nullptr };

	std::array< Voxel, CUBIX_CHUNK_SIZE * CUBIX_CHUNK_SIZE > m_data;

	size_t m_voxelCount{ 0 };

public:
	WorldChunkLayer( WorldChunk& worldChunk, int yLevel );

	CUBIX_GET_R_CR( m_worldChunk, WorldChunk );
	CUBIX_GET_R_CR( m_yLevel, Y );
	CUBIX_GET_R_CR( m_voxelCount, VoxelCount );
	CUBIX_GET_SET_CR_CR( m_nextLayer, NextLayer );
	CUBIX_GET_SET_CR_CR( m_prevLayer, PreviousLayer );

	void fill( Voxel voxel );
	void setVoxel( size_t index, Voxel voxel );
	Voxel getVoxel( size_t index ) const;

	void setVoxel( const glm::ivec2& position, Voxel voxel );
	Voxel getVoxel( const glm::ivec2& position ) const;
};

} // namespace Game

#endif
