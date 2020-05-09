/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk_container.h"

#include "game/world/chunk/world_chunk.h"
#include "game/world/voxel/voxel.h"
#include "game/world/world.h"

#include <shared_mutex>

namespace Game
{

WorldChunkContainer::WorldChunkContainer( World& world ) : m_world( world ) {}

std::shared_ptr< WorldChunk > WorldChunkContainer::getChunk( const ChunkPosition& chunkPos ) const
{
	auto it = m_chunkMap.find( chunkPos );
	return it != m_chunkMap.end() ? it->second : nullptr;
}

std::shared_ptr< WorldChunk > WorldChunkContainer::getOrCreateChunk( const ChunkPosition& chunkPos )
{
	auto chunk = getChunk( chunkPos );
	if( !chunk )
	{
		chunk.reset( new WorldChunk( m_world, chunkPos ) );
		m_chunkMap.insert( { chunkPos, chunk } );
		m_chunkList.push_back( chunk );
	}
	return chunk;
}

void WorldChunkContainer::deleteChunk( const ChunkPosition& chunkPos )
{
	m_chunkMap.erase( chunkPos );
}

bool WorldChunkContainer::isSurrounded( const ChunkPosition& pos ) const
{
	for( int x = -1; x <= 1; ++x )
	{
		for( int y = -1; y <= 1; ++y )
		{
			if( x == 0 && y == 0 )
			{
				continue;
			}

			ChunkPosition chunkPosition{ pos.x + x, pos.y + y };
			if( !getChunk( chunkPosition ) )
			{
				return false;
			}
		}
	}
	return true;
}

void WorldChunkContainer::setVoxel( const WorldPosition& pos, const Voxel& voxel )
{
	auto chunk = getChunk( pos.toChunkPosition() );
	if( chunk )
	{
		chunk->setVoxel( pos.toInnerChunkOffset(), voxel );
	}
}

Voxel WorldChunkContainer::getVoxel( const WorldPosition& pos, const Voxel& _def ) const
{
	auto chunk = getChunk( pos.toChunkPosition() );
	if( !chunk )
	{
		return Voxel();
	}
	return chunk->getVoxel( pos.toInnerChunkOffset() );
}

} // namespace Game