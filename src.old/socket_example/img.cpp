#include <iostream>
#include <stdio.h>
#include <string.h>
#include "comms_img.hpp"


int main (int argc, char const *argv[])
{

    std::thread t = comms::initService();
    comms::msgStruct *msg = new comms::msgStruct;
    msg = comms::getMsgStructRef();
    while (true) { // codigo de raspi img
        msg->ang = 5.5;
    }

    t.join();
    return 0;
}
