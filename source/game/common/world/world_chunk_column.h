/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_COLUMN_H
#define CUBIX_WORLD_CHUNK_COLUMN_H

#include "core/data/container2d.h"

#include <map>
#include <memory>

namespace Game
{

class World;

class WorldChunk;

class WorldChunkColumn
{
public:
	typedef std::map< int, std::shared_ptr< WorldChunk > > ColumnMap;

protected:
	ColumnMap m_column;
	World& m_world;
	glm::ivec2 m_chunkPosition;

	// The top/bottom-most block for a given position
	Core::Container2D< glm::ivec2 > m_yLevelLimits; // unused
public:
	WorldChunkColumn( World& world, const glm::ivec2& chunkPosition );

	CUBIX_GET_R_CR( m_world, World );
	CUBIX_GET_CR( m_chunkPosition, ChunkPosition );
	CUBIX_GET_R_CR( m_column, Chunks );

	ColumnMap::mapped_type getChunk( int yLevel );
	const ColumnMap::mapped_type getChunk( int yLevel ) const;
	ColumnMap::mapped_type createEmptyChunkIfAbsent( int yLevel );
	void deleteChunk( int yLevel );
	size_t size() const;
};

} // namespace Game

#endif
