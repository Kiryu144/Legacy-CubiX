/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_RENDER_WORLD_CHUNK_H
#define CUBIX_RENDER_WORLD_CHUNK_H

#include "core/logic/lockable.h"
#include "core/opengl/attributebuffer.h"
#include "core/math/transform.h"

#include "game/common/world/chunk/world_chunk.h"

#include <atomic>

namespace Game
{

class RenderWorldChunk : public WorldChunk, public Core::Transform
{
protected:
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		Core::Color color;
	};

	static const glm::vec3& GetPosForCube( const Core::MultipleFacing::Face& face, int index );
	static const glm::vec3& GetNormForCube( const Core::MultipleFacing::Face& face );
	int getACColorCorrectionForCube( const Core::MultipleFacing::Face& face,
									 const glm::ivec3& pos,
									 int index );

	Core::AttributeBuffer m_attributeBuffer;
	std::vector< Vertex > m_vertices;

	std::mutex m_uploadMutex;
	bool m_upload{ false };

	std::atomic_bool m_meshGenerated{ false };

public:
	RenderWorldChunk( World& world, const glm::ivec3& chunkPosition );

	CUBIX_GET_R_CR( m_attributeBuffer, AttributeBuffer );

	Core::MultipleFacing findVisibleFaces( const glm::uvec3& pos ) const;

	void regenerateMesh();
	void uploadWhenNeeded();

	bool isMeshGenerated() const;
	void setMeshGenerated();
};

} // namespace Game

#endif