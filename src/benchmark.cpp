#include <iostream>
#include <stdio.h>
#include <string.h>
#include <chrono>
#include <unistd.h>

#include "headers/comms_control.hpp"

#define RUNS                                            1000

int main (int argc, char const *argv[])
{

    int times = new int[RUNS];
    comms::initComms("localhost", 5556);
    for (unsigned long long i = 0; i < RUNS; i++) {
        auto start = std::chrono::high_resolution_clock::now();
            comms::msgStruct msg = comms::getData();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        times[i] = duration.count();
    }

    unsigned long long avg = 0;
    for (unsigned long long i = 0; i < RUNS; i++)
        avg += times[i];
    avg /= RUNS;

    std::cout << "AVG TIME (μs): " << avg << '\n';

    delete times;
    return 0;
}
