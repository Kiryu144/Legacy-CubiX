/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_H
#define CUBIX_WORLD_CHUNK_H

#include "core/data/container2d.h"
#include "core/logic/memory.h"
#include "core/logic/serializeable.h"
#include "core/math/transform.h"
#include "core/opengl/attributebuffer.h"
#include "core/opengl/data/interleaved_attribute.h"

#include "game/client/rendering/renderable.h"
#include "game/common/voxel/voxel_group.h"
#include "game/common/world/world.h"

#include <set>

namespace Game
{

class World;
class Entity;

class WorldChunk : public virtual VoxelGroup,
				   public Core::Transform,
				   public std::mutex,
				   public Renderable
{
protected:
	static const glm::vec3& GetPosForCube( const Core::MultipleFacing::Face& face, int index );
	static const glm::vec3& GetNormForCube( const Core::MultipleFacing::Face& face );
	int getACColorCorrectionForCube( const Core::MultipleFacing::Face& face,
									 const glm::ivec3& pos,
									 int index );

public:
	static unsigned int s_sideLength;
	static glm::ivec3 WorldPosToChunkPos( const glm::vec3& worldPos )
	{
		return glm::ivec3{ std::floor( worldPos.x / s_sideLength ),
						   std::floor( worldPos.y / s_sideLength ),
						   std::floor( worldPos.z / s_sideLength ) };
	}

protected:
	glm::ivec3 m_chunkPosition;

	double m_millisecondsNotSeen{ 0 };
	bool m_terrainGenerated{ false };
	bool m_terrainPopulated{ false };

	World& m_world;

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		Core::Color color;
	};

	// Vertices ready to be uploaded to the GPU if m_uploadVertices == true
	std::vector< Vertex > m_vertexBuffer;
	bool m_uploadVertices{ false };
	bool m_render{ false };

	Core::AttributeBuffer m_attributeBuffer;

public:
	WorldChunk( World& world, const glm::ivec3& chunkPosition = glm::ivec3{ 0, 0, 0 } );

	CUBIX_GET_SET_R_CR( m_chunkPosition, ChunkPosition );
	CUBIX_GET_SET_R_CR( m_millisecondsNotSeen, MillisecondsNotSeen );
	CUBIX_GET_SET_CR_CR( m_terrainGenerated, TerrainGenerated );
	CUBIX_GET_SET_CR_CR( m_terrainPopulated, TerrainPopulated );
	CUBIX_GET_SET_CR_CR( m_render, Render );

	const glm::ivec3 getWorldPosition() const;

	unsigned int getSideLength();

	World& getWorld() const;

	void generateMesh();
	void uploadMesh();

	void render( const View& view, const Projection& projection ) override;

	void serialize( std::ostream& out ) const override;
	void deserialize( std::istream& in ) override;
};

} // namespace Game

#endif
