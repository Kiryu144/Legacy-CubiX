/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world.h"

#include "core/opengl/shader_program.h"

#include "game/rendering/renderer.h"
#include "game/world/chunk/world_chunk_column.h"

namespace Game
{

World::World( Renderer* renderer )
	: WorldChunkContainer( *this ),
	  m_chunkWorker( 4 ),
	  m_chunkFactory( new RenderWorldChunkFactory() ),
	  m_renderer( renderer )
{
}

void World::generateChunk( const glm::ivec3& chunkPosition )
{
	auto lock( m_chunksToGenerate.lockGuard() );
	m_chunksToGenerate.insert( chunkPosition );
}

void World::_generateChunk( const glm::ivec3& chunkPosition )
{
	auto chunk = createChunk( chunkPosition );
	if( chunk != nullptr )
	{
		m_chunkWorker.queue( chunk );
	}
}

void World::update( float deltaTime )
{
	m_chunkWorker.checkForCrash();
	{
		auto lock( m_chunksToGenerate.lockGuard() );
		for( auto& chunkPosition : m_chunksToGenerate )
		{
			_generateChunk( chunkPosition );
		}
		m_chunksToGenerate.clear();
	}

	{
		auto lock( m_chunksToDelete.lockGuard() );
		for( auto& chunkPosition : m_chunksToDelete )
		{
			_deleteChunk( chunkPosition );
		}
		m_chunksToDelete.clear();
	}

	for( auto it = m_allChunks.begin(); it != m_allChunks.end(); )
	{
		if( it->expired() )
		{
			it = m_allChunks.erase( it );
		}
		else
		{
			auto chunk = it->lock();
			chunk->setMillisecondsNotSeen( chunk->getMillisecondsNotSeen() + deltaTime * 1000 );
			if( chunk->getMillisecondsNotSeen() > 500 )
			{
				deleteChunk( chunk->getChunkPosition() );
			}
			++it;
		}
	}
}

/*
void World::insert( const VoxelGroup& voxelGroup, glm::ivec3 position )
{

	glm::ivec3 lowestChunkPos{ IWorldChunk::ChunkPosFromWorldPos( position ) };
	glm::ivec3 affectedChunks{ static_cast< glm::ivec3 >( voxelGroup.getSize() )
								   / glm::ivec3( IWorldChunk::GetSideLength() )
							   + glm::ivec3( 2 ) };

	for( int x = 0; x < affectedChunks.x; ++x )
	{
		for( int y = 0; y < affectedChunks.y; ++y )
		{
			for( int z = 0; z < affectedChunks.z; ++z )
			{
				glm::ivec3 chunkPosition{ lowestChunkPos + glm::ivec3{ x, y, z } };
				auto chunk = getChunk( chunkPosition );
				if( !chunk )
				{
					chunk = createChunk( chunkPosition );
				}

				chunk->WorldChunk::lock();

				glm::ivec3 v
					= position - ( ( chunkPosition )*glm::ivec3( IWorldChunk::GetSideLength() ) );
				chunk->insert( voxelGroup, v );

				chunk->WorldChunk::unlock();
				// m_chunkWorker.queue( chunk );
			}
		}
	}
}
 */

void World::updateForPlayer( const glm::ivec2& chunkPosition )
{
	auto chunkColumn = getChunkColumn( chunkPosition );
	if( chunkColumn == nullptr )
	{
		generateChunk( { chunkPosition.x, 0, chunkPosition.y } );
	}
	else
	{
		for( auto it : chunkColumn->getChunks() )
		{
			it.second->setMillisecondsNotSeen( 0 );
		}
	}
}

void World::_deleteChunk( const glm::ivec3& chunkPosition )
{
	removeChunk( chunkPosition );
}

void World::deleteChunk( const glm::ivec3& chunkPosition )
{
	auto lock( m_chunksToDelete.lockGuard() );
	m_chunksToDelete.insert( chunkPosition );
}

void World::render()
{
	if( m_chunkShader == nullptr )
	{
		auto& shaderRegistry	   = getRenderer()->getShaderRegistry();
		auto shaderKey			   = shaderRegistry.getKey( "world_chunk_shader" ).value();
		m_chunkShader			   = shaderRegistry.getValue( shaderKey );
		m_ambientLightPowerUniform = m_chunkShader->getUniformLocation( "u_ambientLightPower" );
		m_directionalLightPositionUniform
			= m_chunkShader->getUniformLocation( "u_directionalLightPosition" );
		m_skyColorUniform	= m_chunkShader->getUniformLocation( "u_skyColor" );
		m_fogDensityUniform = m_chunkShader->getUniformLocation( "u_density" );
	}

	prepareUniforms( *m_chunkShader );
	for( auto& chunkIt : getAllChunks() )
	{
		if( chunkIt.expired() )
		{
			continue;
		}

		std::shared_ptr< RenderWorldChunk > chunk
			= std::static_pointer_cast< RenderWorldChunk >( chunkIt.lock() );

		chunk->uploadWhenNeeded();
		if( !chunk->isMeshGenerated() || chunk->getMillisecondsNotSeen() > 0
			|| chunk->getAttributeBuffer().getVerticeAmount() == 0 )
		{
			continue;
		}

		m_renderer->render( chunk.get() );
	}
}

void World::prepareUniforms( Core::ShaderProgram& shader )
{
	shader.setUniform( m_ambientLightPowerUniform, 0.8f );
	shader.setUniform( m_directionalLightPositionUniform,
					   glm::vec3{ 5000.0f, -100000.0f, 14400.0f } );
	shader.setUniform( m_skyColorUniform, glm::vec3( 179 / 255.0f, 210 / 255.0f, 238 / 255.0f ) );
	shader.setUniform( m_fogDensityUniform, 0.0004f );
}

size_t World::calculateVoxelMemoryConsumption() const
{
	size_t size{ 0 };
	for( auto& chunk : getAllChunks() )
	{
		auto lock = chunk.lock();
		if( dynamic_cast< WorldChunk* >( lock.get() ) != nullptr )
		{
			size += IWorldChunk::GetVolume() * sizeof( Voxel );
		}
	}
	return size;
}

} // namespace Game