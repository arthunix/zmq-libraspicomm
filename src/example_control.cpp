#include <iostream>
#include <stdio.h>
#include <string.h>
#include "headers/comms_control.hpp"

#define RUNS 1000


int main (int argc, char const *argv[])
{

    comms::initComms();

    while (true) {
        comms::msgStruct msg = comms::getData();
        std::cout << msg.ang << '\n';
        sleep(1);
    }

    return 0;
}
