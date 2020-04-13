/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk.h"

#include <glm/glm.hpp>

namespace Game
{

unsigned int WorldChunk::s_sideLength = 32;

WorldChunk::WorldChunk( World& world, const glm::ivec3& chunkPosition )
	: VoxelGroup( glm::uvec3{ s_sideLength, s_sideLength, s_sideLength } ),
	  m_chunkPosition( chunkPosition ),
	  m_world( world ),
	  m_millisecondsNotSeen( 0 ),
	  m_highestBlock( { m_size.x, m_size.y } )
{
	getPosition() = glm::ivec3{ chunkPosition.x * getSize().x,
								chunkPosition.y * getSize().y,
								chunkPosition.z * getSize().z };
}

void WorldChunk::serialize( std::ostream& out ) const
{
	VoxelGroup::serialize( out );
	out.write( reinterpret_cast< const char* >( &m_chunkPosition ),
			   sizeof( decltype( m_chunkPosition ) ) );
}

void WorldChunk::deserialize( std::istream& in )
{
	VoxelGroup::deserialize( in );
	in.read( reinterpret_cast< char* >( &m_chunkPosition ), sizeof( decltype( m_chunkPosition ) ) );
}

unsigned int WorldChunk::getSideLength()
{
	return s_sideLength;
}

const glm::ivec3 WorldChunk::getWorldPosition() const
{
	return { m_chunkPosition.x * s_sideLength,
			 m_chunkPosition.y * s_sideLength,
			 m_chunkPosition.z * s_sideLength };
}

World& WorldChunk::getWorld() const
{
	return m_world;
}

int WorldChunk::updateHighestBlock( const glm::ivec2& pos )
{
	for( int y = m_size.y - 1; y >= 0; --y )
	{
		if( operator[]( { pos.x, y, pos.y } ).exists() )
		{
			m_highestBlock[ pos ] = y;
			return y;
		}
	}
	return -1;
}

void WorldChunk::updateHighestBlocks()
{
	for( int x = 0; x < m_size.x; ++x )
	{
		for( int z = 0; z < m_size.x; ++z )
		{
			updateHighestBlock( { x, z } );
		}
	}
}

} // namespace Game