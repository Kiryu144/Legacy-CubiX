/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_H
#define CUBIX_WORLD_H

#include "game/proxy.h"
#include "game/world/chunk/world_chunk_container.h"
#include "game/world/chunk/world_chunk_worker.h"
#include "game/world/worldgenerator/world_generator.h"

#include <unordered_set>

namespace Core
{
class AxisAlignedBB;
}

namespace Game
{

class Renderer;
class Entity;
class PlacedVoxel;

class World : public WorldChunkContainer, public Proxy
{
protected:
	WorldChunkWorker m_chunkWorker;
	WorldGenerator m_worldGenerator;
	Renderer* m_renderer;

	void generateChunk( std::shared_ptr< WorldChunk >& worldChunk );
	void populateChunk( std::shared_ptr< WorldChunk >& worldChunk );

	int m_generatedChunks{ 0 };
	int m_populatedChunks{ 0 };
	int m_finishedChunks{ 0 };

public:
	World( Renderer* renderer );

	CUBIX_GET_V( m_generatedChunks, GeneratedChunkCount );
	CUBIX_GET_V( m_populatedChunks, PopulatedChunkCount );
	CUBIX_GET_V( m_finishedChunks, FinishedChunkCount );
	CUBIX_GET_R_CR( m_worldGenerator, WorldGenerator );
	CUBIX_GET_SET_R_CR( m_renderer, Renderer );

	void tick();
	void update();

	void generateMesh( std::shared_ptr< WorldChunk >& worldChunk );
};

} // namespace Game

#endif
