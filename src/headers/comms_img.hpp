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

#include "msg_struct.h"


namespace comms {

    msgStruct *getMsgStructRef();

    void repThread();

    std::thread initService();
}
#endif
