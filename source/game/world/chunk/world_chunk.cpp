/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk.h"

#include "game/world/world.h"

namespace Game
{

WorldChunk::WorldChunk( World& world, const glm::ivec2& chunkPosition )
	: m_world( world ), m_chunkPosition( chunkPosition )
{
	m_data.resize( GetMaxYLevel() - GetMinYLevel() );
}

std::shared_ptr< WorldChunkLayer >& WorldChunk::getLayer( int y )
{
	cubix_assert( y >= GetMinYLevel() && y < GetMaxYLevel(), "Out of bounds" );
	return m_data[ y + ( -GetMinYLevel() ) ];
}

const std::shared_ptr< WorldChunkLayer >& WorldChunk::getLayer( int y ) const
{
	cubix_assert( y >= GetMinYLevel() && y < GetMaxYLevel(), "Out of bounds" );
	return m_data[ y + ( -GetMinYLevel() ) ];
}

std::shared_ptr< WorldChunkLayer >& WorldChunk::getOrCreateLayer( int y )
{
	auto& layer = getLayer( y );
	if( !layer )
	{
		layer.reset( new WorldChunkLayer( *this, y ) );
		m_heightBounds[ 0 ] = std::min( m_heightBounds[ 0 ], y );
		m_heightBounds[ 1 ] = std::max( m_heightBounds[ 1 ], y );
	}
	return layer;
}

void WorldChunk::setVoxel( const glm::uvec3& position, const Voxel& voxel )
{
	auto& layer = getOrCreateLayer( position.y );
	layer->setVoxel( position, voxel );
}

Voxel WorldChunk::getVoxel( const glm::uvec3& position ) const
{
	auto& layer = getLayer( position.y );
	return layer ? layer->getVoxel( { position.x, position.z } ) : Voxel();
}

} // namespace Game