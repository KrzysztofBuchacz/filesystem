#include "filesystem.h"
#include <string.h>
#ifdef _WIN32
const char sep[] = "\\";
#else
const char sep[] = "/";
#include <sys/stat.h>
#include <dirent.h>
#endif

using namespace kbu::filesystem;

path::path(const std::string &p) : _path(p)
{
}

path path::extension() const
{
    size_t s = _path.rfind(sep);
    size_t d = _path.rfind(".");
    if (d > s)
        return _path.substr(d);
    return path(string());
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
    DIR *dir = opendir(path.string().c_str());
    if (dir)
    {
        if (struct dirent *entry = readdir(dir))
        {
            do
            {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                    continue;
                kbu::filesystem::path p(path.string() + sep + entry->d_name);
                ret.push_back(p);
            }
            while ((entry = readdir(dir)) != nullptr);
        }
        closedir(dir);
    }
    return ret;
}

bool kbu::filesystem::is_directory(const path &path)
{
    struct stat st = {};
    if (stat(path.string().c_str(), &st))
        return false;
    return st.st_mode & S_IFDIR;
}
