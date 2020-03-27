/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_RIFF_PARSER_H
#define CUBIX_RIFF_PARSER_H

#include <map>
#include <string>
#include <vector>

namespace Core
{

class RiffParser
{
public:
	typedef unsigned char Byte;

protected:
	struct Chunk
	{
		std::string name;
		Byte* data;
		size_t size;
		std::map< std::string, Chunk > children;
	};

	std::vector< Byte > m_data;
	Chunk m_main;

	void parseFromFile( const std::string& path );
	void parse( Byte* data );
	void readChunk( Byte*& data, Chunk& chunk );
	void printStructure( Chunk& chunk, int indent = 0 );

public:
	RiffParser( const std::string& fpath );

	const Chunk& getMain() const;
};

} // namespace Core

#endif
