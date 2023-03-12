#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "headers/comms_control.hpp"


int main (int argc, char const *argv[])
{

    comms::comms_logger.setDebug();
    comms::initComms();

    while (true) {
        comms::msgStruct msg = comms::getData();
        std::cout << msg.ang << '\n';
        sleep(1);
    }

    return 0;
}
