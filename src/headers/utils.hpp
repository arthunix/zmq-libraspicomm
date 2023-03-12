#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <chrono>

#include <sstream>


namespace utils {

    const std::string currentDateTime() {
        // Get current date/time, format is YYYY-MM-DD.HH-mm-ss

        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        auto str = oss.str();

        return str;
    }

    template <typename T>
    T modulus(T val) {
        if (val >= 0)
            return val;
        return -val;
    }

    class Logger {
    public:
        enum logPriority : unsigned short {Debug = 0, Info, Warning, Error, Critical};
        static unsigned short int DEBUG;

    private:
        unsigned short _priority;
        char* _logFilePath;
        char* _prefix;

        template<typename... Args>
        void _appendToFile(const char* priorityStr, const char* message, Args... args) {
            std::ofstream logFile;
            FILE* pFile;

            const char* loggingPath;
            loggingPath = this->_logFilePath;

            pFile = fopen((const char*) loggingPath, "a+");

            std::fprintf(pFile, "[%s] - %s - %s - ", priorityStr, this->_prefix, currentDateTime().c_str());

            std::fprintf(pFile, message, args...);

            std::fprintf(pFile, ";\n");

            fclose(pFile);

            if (DEBUG) {
                printf("[%s] - %s - %s - ", priorityStr, this->_prefix, currentDateTime().c_str());
                printf(message, args...);
                printf(";\n");
            }
        }

    public:
        Logger() {}
        Logger(char* loggerName, char* logFilePath, unsigned short priority=Info) {
            this->_prefix = loggerName;
            this->_logFilePath = logFilePath;
            this->_priority = priority;
        }

        static void setDebug() {
            DEBUG = 1;
        }

        static void unsetDebug() {
            DEBUG = 0;
        }

        void setPriority(unsigned short priority) {
            this->_priority = priority;
        }

        unsigned short getPriority() {
            return this->_priority;
        }

        // Basic logging funcions:
        template<typename... Args>
        void debug(const char* message, Args... args) {
            if (this->_priority <= Debug)
                this->_appendToFile("DEBUG", message, args...);
        }

        template<typename... Args>
        void info(const char* message, Args... args) {
            if (this->_priority <= Info)
                this->_appendToFile("INFO", message, args...);
        }

        template<typename... Args>
        void warning(const char* message, Args... args) {
            if (this->_priority <= Warning)
                this->_appendToFile("WARNING", message, args...);
        }

        template<typename... Args>
        void error(const char* message, Args... args) {
            if (this->_priority <= Error)
                this->_appendToFile("ERROR", message, args...);
        }

        template<typename... Args>
        void critical(const char* message, Args... args) {
            if (this->_priority <= Critical)
                this->_appendToFile("CRITICAL", message, args...);
        }
    };
}

#endif
