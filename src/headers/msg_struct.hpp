#ifndef MSG_STRUCT_H
#define MSG_STRUCT_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <cstdio>
#include <fstream>

// #ifndef COMMS_DEBUG
// #define COMMS_DEBUG 0
// #endif

namespace comms {
    struct msgStruct {
        float ang;
        float dist;
        float c;
        float d;
    };

    template<typename... Args>
    void log(const char* message, Args... args) {

        time_t     now = time(0);
        struct tm  tstruct;
        char       currTime[80] = {0};
        tstruct = *localtime(&now);
        // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
        // for more information about date/time format
        strftime(currTime, sizeof(currTime), "%Y-%m-%d.%X", &tstruct);

        char log_path[] = "comms.log";

        std::ostringstream oss;
        oss << "[TRACE]" << ":comms:" << currTime << ":";
        auto log_init_str = oss.str();

        std::ofstream logFile;
        FILE* pFile;
        pFile = fopen(log_path, "a+");

        fprintf(pFile, log_init_str.c_str());
        fprintf(pFile, message, args...);
        fprintf(pFile, ";\n");
        fclose(pFile);

        #ifndef COMMS_DEBUG
            printf(log_init_str.c_str());
            printf(message, args...);
            printf(";\n");
        #endif
        // if (COMMS_DEBUG) {
        //     printf(log_init_str.c_str());
        //     printf(message, args...);
        //     printf(";\n");
        // }
    }
}

#endif
