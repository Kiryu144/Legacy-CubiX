#ifndef CUBIX_CORE_FILES_H
#define CUBIX_CORE_FILES_H

#include <string>

namespace DrawIO
{

class FilePath;

struct Files
{
	Files() = delete;

	static bool readAllBytes( const FilePath& fpath, std::string& buffer );
};

} // namespace DrawIO

#endif // CUBIX_CORE_FILES_H
