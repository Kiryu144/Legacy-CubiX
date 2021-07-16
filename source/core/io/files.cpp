#include "files.h"

#include <fstream>
#include <iostream>

#include <core/io/file_path.h>

namespace DrawIO
{

bool Files::readAllBytes( const FilePath& fpath, std::string& buffer )
{
	std::ifstream f( fpath.toString(), std::ios::binary );
	if( f.fail() )
	{
		return false;
	}
	else
	{
		buffer.insert(buffer.begin(), std::istreambuf_iterator< char >( f ), std::istreambuf_iterator< char >() );
		return true;
	}
}

} // namespace DrawIO