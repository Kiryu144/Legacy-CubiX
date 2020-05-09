/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world.h"

#include "game/rendering/renderer.h"
#include "game/rendering/world/world_chunk_renderer.h"
#include "game/world/chunk/world_chunk.h"
#include "game/world/chunk/world_chunk_mesh.h"
#include "game/world/entity/entity.h"

namespace Game
{

World::World( Renderer* renderer )
	: WorldChunkContainer( *this ),
	  Proxy( renderer == nullptr ),
	  m_renderer( renderer ),
	  m_chunkWorker( 4 ),
	  m_worldGenerator( *this )
{
	int range = 10;
	for( int x = -range; x <= range; ++x )
	{
		for( int y = -range; y <= range; ++y )
		{
			getOrCreateChunk( ChunkPosition{ x, y } );
		}
	}
}

void World::tick()
{
	m_generatedChunks = 0;
	m_populatedChunks = 0;
	m_finishedChunks  = 0;

	for( auto chunk : getAllChunks() )
	{
		if( chunk->isWorkedOn() )
		{
			continue;
		}

		if( !chunk->isGenerated() )
		{
			generateChunk( chunk );
			continue;
		}
		++m_generatedChunks;

		if( !chunk->isPopulated() )
		{
			if( isSurrounded( chunk->getChunkPosition() ) )
			{
				populateChunk( chunk );
			}
			continue;
		}
		++m_populatedChunks;

		if( !chunk->isFinished() )
		{
			chunk->setFinished( true );
			generateMesh( chunk );
		}
		++m_finishedChunks;

		if( chunk->getWorldChunkMesh() && !chunk->getWorldChunkMesh()->getVertices().empty() )
		{
			chunk->getVertexBuffer().upload( &chunk->getWorldChunkMesh()->getVertices()[ 0 ],
											 chunk->getWorldChunkMesh()->getVertices().size() );
			chunk->getWorldChunkMesh()->getVertices().clear();
		}
	}
}

void World::update()
{
	for( auto chunk : getAllChunks() )
	{
		if( chunk->isWorkedOn() )
		{
			continue;
		}

		if( m_renderer )
		{
			if( chunk->getVertexBuffer().isValid() )
			{
				m_renderer->getWorldChunkRenderer()->render( chunk );
			}
		}
	}
}

void World::generateChunk( std::shared_ptr< WorldChunk >& worldChunk )
{
	m_chunkWorker.queue( worldChunk, WorldChunkWorker::GENERATE );
}

void World::populateChunk( std::shared_ptr< WorldChunk >& worldChunk )
{
	m_chunkWorker.queue( worldChunk, WorldChunkWorker::POPULATE );
}

void World::generateMesh( std::shared_ptr< WorldChunk >& worldChunk )
{
	m_chunkWorker.queue( worldChunk, WorldChunkWorker::MESH );
}

} // namespace Game