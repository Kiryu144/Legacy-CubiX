/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_WORLD_CHUNK_RENDERER_H
#define CUBIX_WORLD_CHUNK_RENDERER_H

#include "game/rendering/sub_renderer.h"

#include <list>
#include <memory>

namespace Core
{
class ShaderProgram;
}

namespace Game
{

class WorldChunk;

class WorldChunkRenderer : public SubRenderer
{
protected:
	std::list< std::shared_ptr< WorldChunk > > m_chunks;

	std::shared_ptr< Core::ShaderProgram > m_shader;

	int m_ambientLightPowerUniform{ -1 };
	int m_directionalLightPositionUniform{ -1 };
	int m_skyColorUniform{ -1 };
	int m_fogDensityUniform{ -1 };

public:
	WorldChunkRenderer( Renderer& renderer );

	void render( std::shared_ptr< WorldChunk >& chunk );
	void finalize() override;
};

} // namespace Game

#endif
