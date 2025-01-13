// Piotr Pedziwiatr
// 02/2024

#ifndef FILELOCATION_HPP
#define FILELOCATION_HPP

#include <string>
#include "iToString.hpp"

namespace smartnvr20::lib
{
    class FileLocation : public iToString
    {
    public:
        FileLocation(
            std::string _path,
            std::string _file) : path(_path), file(_file) {}

        std::string getPath() const { return path; }
        std::string getFile() const { return file; }

        std::string toString() const override
        {
            return path + file;
        }

    private:
        std::string path;
        std::string file;
    };
} // namespace smartnvr20::lib

#endif // FILELOCATION_HPP
