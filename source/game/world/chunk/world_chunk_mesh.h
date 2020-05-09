/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_MESH_H
#define CUBIX_WORLD_CHUNK_MESH_H

#include "defines.h"

#include "core/cubix_macro.h"
#include "core/data/color.h"

#include "game/world/voxel/voxel.h"
#include "game/world/world_position.h"

#include <memory>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Game
{

class World;
class WorldChunk;

class WorldChunkMesh
{
protected:
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		Core::Color color;
	};

	struct VoxelCluster
	{
		bool exist[ 3 ][ 3 ][ 3 ];
		bool& operator()( int x, int y, int z )
		{
			return exist[ x + 1 ][ y + 1 ][ z + 1 ];
		}

		const bool& operator()( int x, int y, int z ) const
		{
			return exist[ x + 1 ][ y + 1 ][ z + 1 ];
		}

		const bool& operator()( const glm::ivec3& vec ) const
		{
			return operator()( vec.x, vec.y, vec.z );
		}

		VoxelCluster()
		{
			memset( this, false, sizeof( VoxelCluster ) );
		}
	};

	std::vector< Vertex > m_vertices;
	std::shared_ptr< WorldChunk > m_chunks[ 3 ][ 3 ];

	std::shared_ptr< WorldChunk > getChunk( const glm::ivec2& offset );
	const std::shared_ptr< WorldChunk > getChunk( const glm::ivec2& offset ) const;
	Voxel getVoxel( const WorldPosition& position ) const;
	bool isRenderVoxel( const WorldPosition& position ) const;

	void pushFaces( const WorldPosition& pos,
					const VoxelCluster& cluster,
					const Core::Color& color );

public:
	WorldChunkMesh( World& world, const glm::ivec2& chunkPos );

	CUBIX_GET_R_CR( m_vertices, Vertices );

	void generate();
};

} // namespace Game

#endif
