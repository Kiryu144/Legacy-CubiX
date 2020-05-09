/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_CONTAINER_H
#define CUBIX_WORLD_CHUNK_CONTAINER_H

#include "core/cubix_macro.h"

#include "game/world/world_position.h"

#include <list>
#include <memory>
#include <unordered_map>

namespace Game
{

class WorldChunk;
class World;
class Voxel;

class WorldChunkContainer
{
public:
	typedef std::unordered_map< ChunkPosition, std::shared_ptr< WorldChunk > > ChunkMap;
	typedef std::list< std::shared_ptr< WorldChunk > > ChunkList;

protected:
	World& m_world;
	ChunkMap m_chunkMap;
	ChunkList m_chunkList;

public:
	WorldChunkContainer( World& world );

	CUBIX_GET_R_CR( m_chunkList, AllChunks );

	std::shared_ptr< WorldChunk > getChunk( const ChunkPosition& chunkPos ) const;
	std::shared_ptr< WorldChunk > getOrCreateChunk( const ChunkPosition& chunkPos );
	void deleteChunk( const ChunkPosition& chunkPos );
	bool isSurrounded( const ChunkPosition& pos ) const;

	void setVoxel( const WorldPosition& pos, const Voxel& voxel );
	Voxel getVoxel( const WorldPosition& pos, const Voxel& _def ) const;
};

} // namespace Game

#endif
