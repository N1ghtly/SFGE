#include <SFGE/Util/FileLogger.h>

std::ofstream sfge::FileLogger::file;

namespace sfge
{
    void FileLogger::setLogFile(const std::string& filename)
    {
        if(file.is_open())
            file.close();
        file.open(filename.c_str());
    }

    void FileLogger::log(const std::string& logMessage)
    {
        if(file.is_open())
            file << "[LOGGER] " << logMessage << std::endl;
    }
}
