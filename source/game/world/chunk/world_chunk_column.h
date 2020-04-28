/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_COLUMN_H
#define CUBIX_WORLD_CHUNK_COLUMN_H

#include "core/cubix_macro.h"
#include "core/data/multiple_facing.h"

#include <map>
#include <memory>

#include <glm/vec2.hpp>

namespace Game
{

class WorldChunk;
class World;

class WorldChunkColumn
{
public:
	typedef std::map< int, std::shared_ptr< WorldChunk > > ColumnMap;

protected:
	World& m_world;
	glm::ivec2 m_chunkPosition;
	ColumnMap m_column;

	bool m_terrainGenerated{ false };
	bool m_allNeighboursFound{ false };
	unsigned int m_notSeen{ 0 };

public:
	WorldChunkColumn( World& world, const glm::ivec2& chunkPosition );

	CUBIX_GET_R_CR( m_world, World );
	CUBIX_GET_R_CR( m_column, ChunkColumnData );
	CUBIX_GET_CR( m_chunkPosition, ChunkPosition );
	CUBIX_GET_SET_CR_CR( m_notSeen, TicksNotSeen );
	CUBIX_GET_SET_CR_CR( m_terrainGenerated, TerrainGenerated );
	CUBIX_GET_SET_CR_CR( m_allNeighboursFound, AllNeighboursFound );

	// Returns chunk at the given yLevel. Returns nullptr if missing
	std::shared_ptr< WorldChunk > getChunk( int yLevel ) const;

	// Returns a chunk at given yLevel or creates a new one if that one is missing.
	// If so, it returns the new chunk.
	// Chunk will be created as a WorldChunk or RenderWorldChunk. This depends
	// on if a renderer is present in the owning world.
	std::shared_ptr< WorldChunk > getOrCreateChunk( int yLevel );

	// Removed all references to a given chunk at yLevel
	void deleteChunk( int yLevel );

	// Returns amount of chunks present in column
	size_t size() const;

	// Checks if all neighbouring chunks have terrain generated
	bool hasAllNeighbours() const;
};

} // namespace Game

#endif
