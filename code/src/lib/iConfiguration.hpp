// Piotr Pedziwiatr
// 02/2024

#ifndef ICONFIGURATION_HPP
#define ICONFIGURATION_HPP

#include <memory>
#include "FileLocation.hpp"

namespace smartnvr20::lib
{

    class iConfiguration
    {
    public:
        // Pure virtual method to get configuration
        //virtual std::shared_ptr<iConfiguration> getConfig() const = 0;

        //std::string getConfigFile() { return pathAndFileName; }

        iConfiguration(const std::shared_ptr<FileLocation> _pathAndFileName) : pathAndFileName(_pathAndFileName->getPath() + _pathAndFileName->getFile()) {}
        
    protected:
        

        std::string pathAndFileName;
    };

} // namespace smartnvr20::lib

#endif // ICONFIGURATION_HPP