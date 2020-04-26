/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_RENDER_WORLD_CHUNK_H
#define CUBIX_RENDER_WORLD_CHUNK_H

#include "world_chunk.h"

#include "core/data/registry.h"
#include "core/logic/lockable.h"
#include "core/math/transform.h"
#include "core/opengl/attributebuffer.h"

#include <atomic>
#include <bitset>

namespace Game
{

class RenderWorldChunk : public WorldChunk, public Core::Transform
{
protected:
	typedef std::bitset< GetVolume() > SolidVoxelBitset;
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
									 int index,
									 const SolidVoxelBitset ( *bitset )[ 3 ][ 3 ] );

	static bool IsFullRenderVoxel( const glm::ivec3& pos, const SolidVoxelBitset& bitset );
	static bool IsFullRenderVoxelSurr( const glm::ivec3& pos,
									   const SolidVoxelBitset ( *bitset )[ 3 ][ 3 ] );

	Core::AttributeBuffer m_attributeBuffer;
	std::vector< Vertex > m_vertices;

	// A bitset containing a bit for every voxel set to true if that block is solid & exists
	SolidVoxelBitset m_solidVoxelBitset;

	// Is true if the vertices in m_vertices can be safely uploaded to the GPU
	std::atomic_bool m_uploadVertices{ false };

	// Mutex will be locked everytime an upload attempt is started with uploadWhenNeeded()
	// This prevents the m_vertices to be accessed while the uploading is in progress
	std::mutex m_uploadingProcessMutex;

public:
	RenderWorldChunk( World& world, const glm::ivec3& chunkPosition );

	CUBIX_GET_R_CR( m_attributeBuffer, AttributeBuffer );

	Core::MultipleFacing findVisibleFaces( const glm::uvec3& pos,
										   const SolidVoxelBitset ( *bitset )[ 3 ][ 3 ] ) const;

	void setVoxel( const glm::uvec3& position, const Voxel& voxel ) override;

	void regenerateMesh();
	void uploadWhenNeeded();
};

} // namespace Game

#endif
