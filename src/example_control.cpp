#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "headers/comms_control.hpp"

#define COMMS_DEBUG 1

int main (int argc, char const *argv[])
{

    comms::initComms("localhost", 5556);
    std::cout << "connected" << '\n';
    while (true) {
        comms::msgStruct msg = comms::getData();
        std::cout << msg.ang << '\n';
        sleep(1);
    }

    return 0;
}
