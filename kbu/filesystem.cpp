#include "filesystem.h"

using kbu::filesystem;

path::path(const std::string &p) : _path(p)
{
}

path path::extension() const
{
    return _path;
}

std::string path::string() const
{
}

directory_entry::directory_entry(const kbu::filesystem::path &p)
{
}

const path & directory_entry::operator () const
{
}

const path & directory_entry::path() const
{
}

std::vector<directory_entry> directory_iterator(const path &path)
{
}

bool is_directory(const path &path)
{
}
