#ifndef _KBU_FILESYSTEM_H_
#define _KBU_FILESYSTEM_H_

#include <vector>
#include <string>

namespace kbu
{

namespace filesystem
{

class path
{
    std::string _path;

  public:
    path(const std::string &p);
    kbu::filesystem::path extension() const;
    std::string string() const;
};

path operator/(const path& lhs, const path& rhs);

class directory_entry
{
    kbu::filesystem::path _path;

  public:
    directory_entry(const kbu::filesystem::path &p);
    operator const kbu::filesystem::path &() const;
    const kbu::filesystem::path &path() const;
};

std::vector<kbu::filesystem::directory_entry> directory_iterator(const kbu::filesystem::path& dir);

bool is_directory(const kbu::filesystem::path &path);

}

}

#endif // _KBU_FILESYSTEM_H_
