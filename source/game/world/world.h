/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_H
#define CUBIX_WORLD_H

#include "game/world/chunk/chunk_worker.h"
#include "game/world/chunk/world_chunk_container.h"
#include "game/world/chunk/world_chunk_factory.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace Core
{
class AxisAlignedBB;
}

namespace Game
{

class Renderer;
class Entity;
class PlacedVoxel;

class World : public WorldChunkContainer
{
public:
	typedef std::unordered_set< glm::ivec3 > ChunkQueue;

protected:
	ChunkWorker m_chunkWorker;
	Renderer* m_renderer;
	std::unique_ptr< IWorldChunkFactory > m_chunkFactory;
	Core::Lockable< ChunkQueue > m_chunksToGenerate;
	Core::Lockable< ChunkQueue > m_chunksToDelete;

	std::list< std::shared_ptr< Entity > > m_entities;

	std::shared_ptr< Core::ShaderProgram > m_chunkShader;
	int m_ambientLightPowerUniform{ -1 };
	int m_directionalLightPositionUniform{ -1 };
	int m_skyColorUniform{ -1 };
	int m_fogDensityUniform{ -1 };

	void _generateChunk( const glm::ivec3& chunkPosition );
	void _deleteChunk( const glm::ivec3& chunkPosition );

public:
	World( Renderer* renderer );
	virtual ~World() = default;
	virtual void update( float deltaTime );

	CUBIX_GET_R_CR( m_chunkWorker, ChunkWorker );
	CUBIX_GET_CR( m_chunkFactory, ChunkFactory );
	CUBIX_GET_SET_R_CR( m_renderer, Renderer );

	// void insert( const VoxelGroup& voxelGroup, glm::ivec3 position );
	void updateForPlayer( const glm::ivec2& chunkPosition );
	void summonEntity( std::shared_ptr< Entity > m_entity );
	void getVoxels( const Core::AxisAlignedBB& aabb, std::list< PlacedVoxel >& buffer );

	void prepareUniforms( Core::ShaderProgram& shader );
	void render();

	size_t calculateVoxelMemoryConsumption() const;

	// Thread safe
	void generateChunk( const glm::ivec3& chunkPosition );
	void deleteChunk( const glm::ivec3& chunkPosition );
};

} // namespace Game

#endif
