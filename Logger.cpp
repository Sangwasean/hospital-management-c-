#include "Logger.h"
#include <iostream>

Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error opening log file!" << std::endl;
    } else {
        // Write header if file is empty
        logFile.seekp(0, std::ios::end);
        if (logFile.tellp() == 0) {
            logFile << "Timestamp,Action,EntityType,EntityID,Details\n";
        }
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

std::string Logger::getCurrentDateTime() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Logger::log(const std::string& action, const std::string& entityType,
                 const std::string& entityId, const std::string& details) {
    if (logFile.is_open()) {
        logFile << getCurrentDateTime() << ","
                << action << ","
                << entityType << ","
                << entityId << ","
                << details << "\n";
        logFile.flush();
    }
}