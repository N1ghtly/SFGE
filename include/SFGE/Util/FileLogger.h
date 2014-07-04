#ifndef FILELOGGER_H
#define FILELOGGER_H
#include <string>
#include <fstream>

namespace sfge
{
    /// \brief A logger that writes messages to text files. Convenient for debugging.
    struct FileLogger
    {
        public:
            /// \brief Set the logging file.
            static void setLogFile(const std::string& filename);

            /// \brief Log to the currently set file. If no file is set, the function does nothing.
            static void log(const std::string& logMessage);

        private:
            static std::ofstream file;
    };
}
#endif // FILELOGGER_H
