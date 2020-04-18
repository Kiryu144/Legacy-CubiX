/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_H
#define CUBIX_WORLD_H

#include "core/cubix_macro.h"
#include "core/logic/lockable.h"
#include "core/logic/memory.h"
#include "core/math/glm_math.h"

#include "game/client/rendering/renderer.h"
#include "game/common/voxel/voxel_group.h"
#include "game/common/world/chunk/chunk_worker.h"
#include "game/common/world/chunk/world_chunk_factory.h"
#include "game/common/world/world_chunk_column.h"
#include "game/common/world/world_chunk_container.h"

#include <set>
#include <unordered_map>
#include <unordered_set>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace Game
{

class Renderer;

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

	std::shared_ptr<Core::ShaderProgram> m_chunkShader;
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

	void insert( const VoxelGroup& voxelGroup, glm::ivec3 position );
	void updateForPlayer( const glm::ivec2& chunkPosition );

	void prepareUniforms(Core::ShaderProgram& shader);
	void render();

	// Thread safe
	void generateChunk( const glm::ivec3& chunkPosition );
	void deleteChunk( const glm::ivec3& chunkPosition );
};

} // namespace Game

#endif
