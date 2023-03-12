#include <iostream>
#include <stdio.h>
#include <string.h>
#include "headers/comms_img.hpp"

#define COMMS_DEBUG 1

int main (int argc, char const *argv[])
{

    comms::initService(5556);
    comms::msgStruct *msg = new comms::msgStruct;
    msg = comms::getMsgStructRef();
    while (true) { // codigo de raspi img
        msg->ang = 5.5;
    }

    // t.join();
    return 0;
}
