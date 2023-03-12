// To install correct version of zmq lib, run:
// wget https://github.com/zeromq/zeromq4-1/releases
// tar xvf zeromq-4.1.4.tar.gz
// cd zeromq-4.1.4/
// sudo ./configure
// sudo make install

#ifndef COMMS_CONTROL_H
#define COMMS_CONTROL_H

#include <zmq.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "msg_struct.hpp"
// #include "utils.hpp"


namespace comms {

    // utils::Logger comms_logger = utils::Logger("ControlComms", "ControlComms.log", utils::Logger::Info);

    void initComms(char *ip, unsigned port);

    msgStruct getData();

}
#endif
