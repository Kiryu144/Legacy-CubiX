/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_COLUMN_H
#define CUBIX_WORLD_CHUNK_COLUMN_H

#include "game/common/world/chunk/i_world_chunk.h"
#include "core/cubix_macro.h"

#include <map>
#include <memory>
#include <glm/vec2.hpp>

namespace Game
{

class World;

class WorldChunk;

class WorldChunkColumn
{
public:
	typedef std::map< int, std::shared_ptr< IWorldChunk > > ColumnMap;

protected:
	ColumnMap m_column;
	World& m_world;
	glm::ivec2 m_chunkPosition;

public:
	WorldChunkColumn( World& world, const glm::ivec2& chunkPosition );

	CUBIX_GET_R_CR( m_world, World );
	CUBIX_GET_CR( m_chunkPosition, ChunkPosition );
	CUBIX_GET_R_CR( m_column, Chunks );

	ColumnMap::mapped_type getChunk( int yLevel );
	const ColumnMap::mapped_type getChunk( int yLevel ) const;
	ColumnMap::mapped_type createEmptyChunkIfAbsent( int yLevel );
	void removeChunk( int yLevel );
	size_t size() const;
};

} // namespace Game

#endif
