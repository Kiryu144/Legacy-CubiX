/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "world_chunk.h"

namespace Game
{

unsigned int WorldChunk::s_sideLength = 32;

WorldChunk::WorldChunk( const glm::ivec3& chunkPosition )
	: VoxelGroup( glm::uvec3{ s_sideLength, s_sideLength, s_sideLength } ),
	  m_chunkPosition( chunkPosition )
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

const glm::ivec3& WorldChunk::getChunkPosition() const
{
	return m_chunkPosition;
}

void WorldChunk::setChunkPosition( const glm::ivec3& chunkPosition )
{
	m_chunkPosition = chunkPosition;
}

} // namespace Game