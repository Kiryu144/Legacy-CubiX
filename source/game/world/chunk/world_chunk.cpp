/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk.h"

#include "core/opengl/data/interleaved_attribute.h"

#include "game/world/chunk/world_chunk_layer.h"
#include "game/world/world.h"

namespace Game
{

WorldChunk::WorldChunk( World& world, const ChunkPosition& chunkPosition )
	: m_world( world ),
	  m_chunkPosition( chunkPosition ),
	  m_vertexBuffer( Core::InterleavedVertNormColAttribute ),
	  m_data( GetMaxYLevel() - GetMinYLevel() )
{
	m_transform.getPosition() = chunkPosition.toWorldPosition();
}

std::shared_ptr< WorldChunkLayer >& WorldChunk::getLayer( int y )
{
	cubix_assert( IsInRange( y ), "Out of bounds" );
	return m_data[ y + ( -GetMinYLevel() ) ];
}

const std::shared_ptr< WorldChunkLayer >& WorldChunk::getLayer( int y ) const
{
	cubix_assert( IsInRange( y ), "Out of bounds" );
	return m_data[ y + ( -GetMinYLevel() ) ];
}

std::shared_ptr< WorldChunkLayer > WorldChunk::getLayerOrNull( int y )
{
	if( !IsInRange( y ) )
	{
		return { nullptr };
	}
	return getLayer( y );
}

const std::shared_ptr< WorldChunkLayer > WorldChunk::getLayerOrNull( int y ) const
{
	if( !IsInRange( y ) )
	{
		return { nullptr };
	}
	return getLayer( y );
}

std::shared_ptr< WorldChunkLayer >& WorldChunk::getOrCreateLayer( int y )
{
	auto& layer = getLayer( y );
	if( !layer )
	{
		layer.reset( new WorldChunkLayer( *this, y ) );
		auto topLayer	 = getLayerOrNull( y + 1 );
		auto bottomLayer = getLayerOrNull( y - 1 );

		if( topLayer )
		{
			topLayer->setPreviousLayer( layer.get() );
			layer->setNextLayer( topLayer.get() );
		}

		if( bottomLayer )
		{
			bottomLayer->setNextLayer( layer.get() );
			layer->setPreviousLayer( bottomLayer.get() );
		}

		m_heightBounds[ 0 ] = std::min( m_heightBounds[ 0 ], y );
		m_heightBounds[ 1 ] = std::max( m_heightBounds[ 1 ], y );
	}
	return layer;
}

void WorldChunk::setVoxel( const WorldPosition& position, Voxel voxel )
{
	auto& layer = getOrCreateLayer( position.y );
	layer->setVoxel( position.toLayerPosition(), voxel );
}

Voxel WorldChunk::getVoxel( const WorldPosition& position ) const
{
	auto& layer = getLayer( position.y );
	return layer ? layer->getVoxel( position.toLayerPosition() ) : Voxel();
}

void WorldChunk::fill( Voxel voxel, int radius )
{

	for( int y = -radius; y <= radius; ++y )
	{
		auto layer = getOrCreateLayer( y );
		if( layer )
		{
			layer->fill( voxel );
		}
	}
}

} // namespace Game