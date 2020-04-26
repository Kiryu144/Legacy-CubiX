/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world.h"

#include "core/opengl/shader_program.h"

#include "game/rendering/renderer.h"
#include "game/rendering/world/gizmo_renderer.h"
#include "game/world/chunk/world_chunk.h"
#include "game/world/chunk/world_chunk_column.h"
#include "game/world/entity/entity.h"

#include <glm/gtx/string_cast.hpp>

namespace Game
{

World::World( Renderer* renderer )
	: WorldChunkContainer( *this ),
	  m_chunkWorker( 4 ),
	  m_renderer( renderer ),
	  m_worldGenerator( *this )
{
}

void World::update( float deltaTime )
{
	m_chunkWorker.checkForCrash();

	for( auto& entity : m_entities )
	{
		entity->update( *this, deltaTime );
		m_renderer->getGizmoRenderer()->drawCube( *entity, { 255, 0, 255, 255 } );
	}
}

void World::updateForPlayer( const glm::ivec2& chunkPosition )
{
	if( getChunkColumn( chunkPosition ) == nullptr )
	{
		m_chunkWorker.queue( getOrCreateChunkColumn( chunkPosition ),
							 ChunkWorker::GENERATE_TERRAIN );
	}
}

size_t World::calculateVoxelMemoryConsumption() const
{
	return getAllChunks().size() * WorldChunk::GetVolume() * sizeof( Voxel );
}

void World::summonEntity( std::shared_ptr< Entity > m_entity )
{
	m_entities.push_back( m_entity );
}

std::optional< glm::ivec3 > World::raycastBlocks( const glm::vec3& start,
												  const glm::vec3& direction,
												  int maxDistance ) const
{
	glm::vec3 directionNorm{ glm::normalize( direction ) };
	for( glm::vec3 pos = start; maxDistance > 0; pos += directionNorm, --maxDistance )
	{
		if( getVoxel( pos ).exists() )
		{
			return glm::ivec3( pos );
		}
	}
	return {};
}

} // namespace Game