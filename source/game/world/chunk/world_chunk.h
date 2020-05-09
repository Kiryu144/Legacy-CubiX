/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_H
#define CUBIX_WORLD_CHUNK_H

#include "core/cubix_macro.h"
#include "core/math/transform.h"
#include "core/opengl/attributebuffer.h"

#include "game/world/voxel/voxel.h"
#include "game/world/world_position.h"

#include <cmath>
#include <memory>
#include <vector>

namespace Game
{

class World;
class WorldChunkLayer;
class Entity;
class Voxel;
class WorldChunkMesh;

class WorldChunk
{
public:
	static constexpr int GetMinYLevel()
	{
		return -512;
	}

	static constexpr int GetMaxYLevel()
	{
		return 512;
	}

	static bool IsInRange( int yLevel )
	{
		return yLevel >= GetMinYLevel() && yLevel < GetMaxYLevel();
	}

protected:
	World& m_world;
	ChunkPosition m_chunkPosition;
	Core::AttributeBuffer m_vertexBuffer;
	Core::Transform m_transform;
	std::shared_ptr< WorldChunkMesh > m_worldChunkMesh;

	std::vector< std::shared_ptr< WorldChunkLayer > > m_data;
	glm::ivec2 m_heightBounds{ 0, 0 };

	bool m_isWorkedOn{ false };
	bool m_generated{ false };
	bool m_populated{ false };
	bool m_finished{ false };

public:
	WorldChunk( World& world, const ChunkPosition& chunkPosition );

	CUBIX_GET_SET_BOOL( m_isWorkedOn, WorkedOn );
	CUBIX_GET_SET_BOOL( m_generated, Generated );
	CUBIX_GET_SET_BOOL( m_populated, Populated );
	CUBIX_GET_SET_BOOL( m_finished, Finished );
	CUBIX_GET_R_CR( m_vertexBuffer, VertexBuffer );
	CUBIX_GET_R_CR( m_world, World );
	CUBIX_GET_R_CR( m_transform, Transform );
	CUBIX_GET_R_CR( m_worldChunkMesh, WorldChunkMesh );
	CUBIX_GET_CR( m_chunkPosition, ChunkPosition );
	CUBIX_GET_V( m_chunkPosition[ 0 ], LowestLayer );
	CUBIX_GET_V( m_chunkPosition[ 1 ], HighestLayer );

	std::shared_ptr< WorldChunkLayer >& getLayer( int y );
	const std::shared_ptr< WorldChunkLayer >& getLayer( int y ) const;
	std::shared_ptr< WorldChunkLayer > getLayerOrNull( int y );
	const std::shared_ptr< WorldChunkLayer > getLayerOrNull( int y ) const;
	std::shared_ptr< WorldChunkLayer >& getOrCreateLayer( int y );

	void fill( Voxel voxel, int radius );
	void setVoxel( const WorldPosition& position, Voxel voxel );
	Voxel getVoxel( const WorldPosition& position ) const;
};

} // namespace Game

#endif
