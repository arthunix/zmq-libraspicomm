/*
MIT License

Copyright (c) 2023 Daniel Lombardi de Oliveira
Copyright (c) 2023 Arthur Eugenio Silverio

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MSG_STRUCT_H
#define MSG_STRUCT_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <cstdio>
#include <fstream>


namespace comms {
    struct msgStruct {
        float ang;
        float dist;
        float c;
        float d;
    };

    template<typename... Args>
    void log(const char* message, Args... args) {
#ifndef COMMS_LOG
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
    #endif // COMMS_DEBUG

#endif // COMMS_LOG
    }
}

#endif
