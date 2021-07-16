#ifndef CUBIX_CORE_FILE_PATH_H
#define CUBIX_CORE_FILE_PATH_H

#include <initializer_list>
#include <list>
#include <string>

namespace DrawIO
{

class FilePath
{
private:
	std::list< std::string > m_path;

public:
	static const wchar_t delimiter;

	FilePath( const std::initializer_list< std::string >& args = {} );
	FilePath( const std::string& path );

	FilePath& append( const std::initializer_list< std::string >& args );
	FilePath& append( const FilePath& filePath );

	void toString( std::string& buffer ) const;
	std::string toString() const;
};

} // namespace DrawIO

#endif // CUBIX_CORE_FILE_PATH_H
