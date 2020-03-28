/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_client.h"

namespace Game
{

WorldClient::WorldClient() : World( Proxy::CLIENT ) {}

void WorldClient::draw( Core::ShaderProgram& shader,
						const glm::mat4& view,
						const glm::mat4& projection )
{
	if( getProxy() != Proxy::CLIENT )
	{
		return;
	}

	shader.bind();
	shader.setUniform( "u_projection", projection );
	shader.setUniform( "u_view", view );
	shader.setUniform( "u_ambientLightPower", 0.8f );
	shader.setUniform( "u_directionalLightPower", 1.0f );
	shader.setUniform( "u_directionalLightPosition", glm::vec3{ 5000.0f, -100000.0f, 14400.0f } );

	for( auto& key : m_chunks )
	{
		WorldChunk* chunk = key.second.get();

		if( chunk->getVertices().getVerticeAmount() == 0 )
		{
			continue;
		}

		shader.setUniform( "u_transformation", chunk->getMatrix() );

		chunk->getVertices().bind( 0 );
		chunk->getNormals().bind( 1 );
		chunk->getColors().bind( 2 );

		glDrawArrays( GL_TRIANGLES, 0, chunk->getVertices().getVerticeAmount() );
	}
}

} // namespace Game
