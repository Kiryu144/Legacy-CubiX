/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_COLUMN_H
#define CUBIX_WORLD_CHUNK_COLUMN_H

#include "core/cubix_macro.h"

#include <map>
#include <memory>

#include <glm/vec2.hpp>

namespace Game
{

class IWorldChunk;
class World;

class WorldChunkColumn
{
public:
	typedef std::map< int, std::shared_ptr< IWorldChunk > > ColumnMap;

protected:
	ColumnMap m_column;
	World& m_world;
	glm::ivec2 m_chunkPosition;

	bool m_isGenerated{ false };
	bool m_isPopulated{ false };

public:
	WorldChunkColumn( World& world, const glm::ivec2& chunkPosition );

	CUBIX_GET_R_CR( m_world, World );
	CUBIX_GET_CR( m_chunkPosition, ChunkPosition );
	CUBIX_GET_R_CR( m_column, Chunks );
	CUBIX_GET_SET_CR_CR( m_isGenerated, IsGenerated );
	CUBIX_GET_SET_CR_CR( m_isPopulated, IsPopulated );

	ColumnMap::mapped_type getChunk( int yLevel );
	const ColumnMap::mapped_type getChunk( int yLevel ) const;
	ColumnMap::mapped_type createEmptyChunkIfAbsent( int yLevel );
	void removeChunk( int yLevel );
	size_t size() const;
};

} // namespace Game

#endif
