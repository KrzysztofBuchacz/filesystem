#include "filesystem.h"
#include <sys/stat.h>

using namespace kbu::filesystem;

path::path(const std::string &p) : _path(p)
{
}

path path::extension() const
{
    return _path;
}

std::string path::string() const
{
    return _path;
}

directory_entry::directory_entry(const kbu::filesystem::path &p) : _path(p)
{
}

directory_entry::operator const kbu::filesystem::path & () const
{
    return _path;
}

const kbu::filesystem::path & directory_entry::path() const
{
     return _path;
}

std::vector<directory_entry> kbu::filesystem::directory_iterator(const path &path)
{
    std::vector<directory_entry> ret;
    return ret;
}

bool kbu::filesystem::is_directory(const path &path)
{
    struct stat st = {};
    if (stat(path.string().c_str(), &st))
        return false;
    return st.st_mode & S_IFDIR;
}
