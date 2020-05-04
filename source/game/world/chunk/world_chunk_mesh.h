/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_MESH_H
#define CUBIX_WORLD_CHUNK_MESH_H

#include "defines.h"
#include "world_chunk.h"

#include <array>

#include <glm/vec2.hpp>

namespace Game
{

class World;

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
	};

	std::vector< Vertex > m_vertices;
	std::shared_ptr< WorldChunk > m_chunks[ 3 ][ 3 ];

	std::shared_ptr< WorldChunk > getChunk( const glm::ivec2& offset );

public:
	WorldChunkMesh( World& world, const glm::ivec2& chunkPos );

	void generate();
};

} // namespace Game

#endif
