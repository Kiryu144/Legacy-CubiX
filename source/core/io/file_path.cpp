#include "file_path.h"

namespace DrawIO
{

#if _WIN32
const wchar_t FilePath::delimiter = '\\';
#else
const wchar_t FilePath::delimiter = '/';
#endif

FilePath::FilePath( const std::initializer_list< std::string >& args ) : m_path( args ) {}

FilePath::FilePath( const std::string& path )
{
	// I'm sure there is some fancy c++ version of the following code.
	for( int i = 0, k = 0; i < path.length(); ++i )
	{
		if( path.at( i ) == delimiter )
		{
			std::string part = path.substr( k, i - k );
			k += part.length() + 1;
			if( !part.empty() )
			{
				m_path.push_back( part );
			}
		}
	}
}

FilePath& FilePath::append( const std::initializer_list< std::string >& args )
{
	m_path.insert( m_path.end(), args.begin(), args.end() );
	return *this;
}

FilePath& FilePath::append( const FilePath& filePath )
{
	m_path.insert( m_path.end(), filePath.m_path.begin(), filePath.m_path.end() );
	return *this;
}

void FilePath::toString( std::string& buffer ) const
{
	buffer.clear();

	for( auto it = m_path.begin(); it != m_path.end(); )
	{
		buffer.insert( buffer.end(), it->begin(), it->end() );
		if (++it != m_path.end())
		{
			buffer.push_back( delimiter );
		}
	}
}

std::string FilePath::toString() const
{
	std::string buf;
	toString( buf );
	return buf;
}

} // namespace DrawIO