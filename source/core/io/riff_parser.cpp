/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "riff_parser.h"

#include <fstream>
#include <iostream>

namespace Core
{

RiffParser::RiffParser( const std::string& fpath )
{
	parseFromFile( fpath );
}

void RiffParser::parseFromFile( const std::string& path )
{
	std::ifstream f( path, std::ios::binary );
	m_data.assign( std::istreambuf_iterator< char >( f ), std::istreambuf_iterator< char >() );
	Byte* start = static_cast< Byte* >( &m_data.at( 0 ) );
	parse( start );
}

void RiffParser::parse( RiffParser::Byte* data )
{
	data += 8; // Skip type and version
	readChunk( data, m_main );
}

void RiffParser::readChunk( Byte*& data, RiffParser::Chunk& chunk )
{
	Byte* start = data;
	chunk.name	= std::string( reinterpret_cast< char* >( data ), 4 );
	data += 4;
	uint32_t numBytesChunkContent = *reinterpret_cast< uint32_t* >( data );
	data += 4;
	uint32_t numBytesChildrenChunks = *reinterpret_cast< uint32_t* >( data );
	data += 4;
	chunk.data = data;
	data += numBytesChunkContent;
	chunk.size = numBytesChunkContent;

	size_t totalSize = 12 + numBytesChunkContent + numBytesChildrenChunks;
	while( data < start + totalSize )
	{
		Chunk child;
		readChunk( data, child );
		chunk.children[ child.name ] = child;
	}
}

void RiffParser::printStructure( RiffParser::Chunk& chunk, int indent )
{
	for( int i = 0; i < indent; ++i )
	{
		std::cout << " ";
	}
	std::cout << chunk.name << ": " << chunk.size << " Bytes" << std::endl;

	for( auto it = chunk.children.begin(); it != chunk.children.end(); ++it )
	{
		printStructure( it->second, indent + 4 );
	}
}

const RiffParser::Chunk& RiffParser::getMain() const
{
	return m_main;
}

} // namespace Core