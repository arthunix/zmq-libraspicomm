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
#include <pthread.h>
#include <unistd.h>
#include <thread>
#include <string>


#include "msg_struct.hpp"
// #include "utils.hpp"

namespace comms {

    // utils::Logger comms_logger = utils::Logger("ImgComms", "ImgComms.log", utils::Logger::Info);

    msgStruct *getMsgStructRef();

    void repThread();

    std::thread initService(unsigned port);
}
#endif
