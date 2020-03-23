/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world.h"

namespace Game
{

World::World()
{
	m_shaderProgram.compileShaderFromFile( "basic.vert", Core::ShaderProgram::VERTEX_SHADER )
		.compileShaderFromFile( "basic.frag", Core::ShaderProgram::FRAGMENT_SHADER )
		.link();
}

void World::loadOrCreate( const glm::uvec3& position )
{
	auto it = m_chunks.find( position );
	if( it == m_chunks.end() )
	{
		// https://en.cppreference.com/w/cpp/utility/tuple/forward_as_tuple
		m_chunks.emplace( std::piecewise_construct,
						  std::forward_as_tuple( position ),
						  std::forward_as_tuple( position ) );
		WorldChunk& chunk = m_chunks.find( position )->second;
		chunk.generateFlat( 8 );
	}
}

void World::draw( const glm::mat4& view, const glm::mat4& projection )
{
	m_shaderProgram.bind();
	m_shaderProgram.setUniform( "u_projection", projection );
	m_shaderProgram.setUniform( "u_view", view );
	m_shaderProgram.setUniform( "u_ambientLightPower", 0.6f );
	m_shaderProgram.setUniform( "u_directionalLightPower", 0.9f );
	m_shaderProgram.setUniform( "u_directionalLightPosition", { 1000.0f, 0.0f, 0.0f } );

	for( auto& key : m_chunks )
	{
		WorldChunk& chunk = key.second;

		if( chunk.getVertices().getVerticeAmount() == 0 )
		{
			continue;
		}

		m_shaderProgram.setUniform( "u_transformation", chunk.getMatrix() );

		chunk.getVertices().bind( 0 );
		chunk.getNormals().bind( 1 );
		chunk.getColors().bind( 2 );

		glDrawArrays( GL_TRIANGLES, 0, chunk.getVertices().getVerticeAmount() );
	}
}

} // namespace Game