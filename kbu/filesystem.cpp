#include "filesystem.h"
#include <string.h>
#ifdef _WIN32
const char sep[] = "\\";
#include "Windows.h"
#include <tchar.h>
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

std::vector<directory_entry> kbu::filesystem::directory_iterator(const path &dir)
{
    std::vector<directory_entry> ret;
#ifdef _WIN32
    WIN32_FIND_DATA data = {};
    path wild = dir / path(std::string("*"));
#ifdef _UNICODE
    wchar_t wpath[_MAX_PATH] = {};
    size_t length = 0;
    ::mbstowcs_s(&length, wpath, _MAX_PATH, wild.c_str(), _TRUNCATE);
    HANDLE hFile = ::FindFirstFile(wpath, &data);
#else
    HANDLE hFile = ::FindFirstFile(wild.string().c_str(), &data);
#endif
    if (hFile != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (_tcscmp(data.cFileName, _T(".")) == 0 || _tcscmp(data.cFileName, _T("..")) == 0)
                continue;
#ifdef _UNICODE
            char apath[_MAX_PATH] = {};
            length = 0;
            ::wcstombs_s(&length, apath, _MAX_PATH, data.cFileName, _TRUNCATE);
            ret.push_back(ScalarisFileSystem::Merge(path, apath));
#else
            kbu::filesystem::path p = dir / path(data.cFileName);
            ret.push_back(p);
#endif
        } while (::FindNextFile(hFile, &data));
        ::FindClose(hFile);
    }
#else
    DIR *pdir = opendir(dir.string().c_str());
    if (pdir)
    {
        if (struct dirent *entry = readdir(pdir))
        {
            do
            {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                    continue;
                kbu::filesystem::path p = dir / path(entry->d_name);
                ret.push_back(p);
            } while ((entry = readdir(pdir)) != nullptr);
        }
        closedir(pdir);
    }
#endif
    return ret;
}

bool kbu::filesystem::is_directory(const path &path)
{
    struct stat st = {};
    if (stat(path.string().c_str(), &st))
        return false;
    return st.st_mode & S_IFDIR;
}

path kbu::filesystem::operator/(const path& lhs, const path& rhs)
{
    std::string ret(lhs.string());
    if (!ret.empty() && ret.back() != sep[0])
        ret += sep;
    ret += rhs.string();
    return path(ret);
}
