#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>

class Logger {
private:
    std::ofstream logFile;
    std::string getCurrentDateTime();

public:
    Logger(const std::string& filename);
    ~Logger();

    void log(const std::string& action, const std::string& entityType,
             const std::string& entityId, const std::string& details = "");
};

#endif