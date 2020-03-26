/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world.h"

namespace Game
{

World::World( Proxy proxy ) : ProxySided( proxy ) {}

void World::loadOrCreate( const glm::ivec3& position )
{
	auto it = m_chunks.find( position );
	if( it == m_chunks.end() )
	{
		// https://en.cppreference.com/w/cpp/utility/tuple/forward_as_tuple
		m_chunks.emplace( std::piecewise_construct,
						  std::forward_as_tuple( position ),
						  std::forward_as_tuple( position ) );
		WorldChunk& chunk = m_chunks.find( position )->second;
		chunk.generateBasicNoise();
	}
}

void World::draw( Core::ShaderProgram& shader, const glm::mat4& view, const glm::mat4& projection )
{
	cubix_assert( getProxy() == Proxy::CLIENT, "Invalid proxy" );

	shader.bind();
	shader.setUniform( "u_projection", projection );
	shader.setUniform( "u_view", view );
	shader.setUniform( "u_ambientLightPower", 0.8f );
	shader.setUniform( "u_directionalLightPower", 1.0f );
	shader.setUniform( "u_directionalLightPosition", { 5000.0f, -100000.0f, 14400.0f } );

	for( auto& key : m_chunks )
	{
		WorldChunk& chunk = key.second;

		if( chunk.getVertices().getVerticeAmount() == 0 )
		{
			continue;
		}

		shader.setUniform( "u_transformation", chunk.getMatrix() );

		chunk.getVertices().bind( 0 );
		chunk.getNormals().bind( 1 );
		chunk.getColors().bind( 2 );

		glDrawArrays( GL_TRIANGLES, 0, chunk.getVertices().getVerticeAmount() );
	}
}

void World::update( float deltaTime )
{
	for( auto it = m_entities.begin(); it != m_entities.end(); ++it )
	{
		Entity* entity = it->get();

		if( entity->isRemove() )
		{
			it = m_entities.erase( it );
			continue;
		}

		entity->update( deltaTime );
	}
}

} // namespace Game