/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world.h"

#include "core/opengl/shader_program.h"

#include "game/rendering/renderer.h"
#include "game/rendering/world/gizmo_renderer.h"
#include "game/world/chunk/world_chunk.h"
#include "game/world/entity/entity.h"

#include <glm/gtx/string_cast.hpp>

namespace Game
{

World::World( Renderer* renderer ) : WorldChunkContainer( *this ), m_renderer( renderer )
{
	int range = 10;
	for( int x = -range; x <= range; ++x )
	{
		for( int y = -range; y <= range; ++y )
		{
			getOrCreateChunk( { x, y } );
		}
	}
}

void World::tick()
{
	for( auto& entity : m_entities )
	{
		entity->tick( *this, CUBIX_MS_PER_TICK );
	}
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