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

#include "game/rendering/renderable.h"

#include <atomic>
#include <bitset>

namespace Game
{

class RenderWorldChunk : public WorldChunk, public Core::Transform, public Renderable
{
protected:
	typedef std::bitset< GetVolume() > FullRenderVoxelBitset;
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
									 const FullRenderVoxelBitset ( *bitset )[ 3 ][ 3 ] );

	static bool IsFullRenderVoxel( const glm::ivec3& pos, const FullRenderVoxelBitset& bitset );
	static bool IsFullRenderVoxelSurr( const glm::ivec3& pos,
									   const FullRenderVoxelBitset ( *bitset )[ 3 ][ 3 ] );

	Core::AttributeBuffer m_attributeBuffer;
	std::vector< Vertex > m_vertices;

	FullRenderVoxelBitset m_renderableVoxels;

	std::mutex m_uploadMutex;
	bool m_upload{ false };

	Core::RegistryKey m_shaderKey;

	std::atomic_bool m_meshGenerated{ false };

public:
	RenderWorldChunk( World& world, const glm::ivec3& chunkPosition );

	Core::MultipleFacing findVisibleFaces(
		const glm::uvec3& pos, const FullRenderVoxelBitset ( *bitset )[ 3 ][ 3 ] ) const;

	void setVoxel( const glm::uvec3& position, const Voxel& voxel ) override;

	void regenerateMesh();
	void uploadWhenNeeded();

	bool isMeshGenerated() const;
	void setMeshGenerated();

	void setUniforms( Core::ShaderProgram& shader ) override;
	Core::RegistryKey getShader() override;
	Core::AttributeBuffer& getAttributeBuffer() override;
};

} // namespace Game

#endif