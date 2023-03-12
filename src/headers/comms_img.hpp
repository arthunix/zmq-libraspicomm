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

    msgStruct *global_bss_struct = new msgStruct;

    zmq::context_t context(1);
    zmq::socket_t global_socket(context, zmq::socket_type::rep);

    msgStruct *getMsgStructRef() {
        return global_bss_struct;
    }

    void repThread() {
        std::cout << "listener thread init" << '\n';
        char ready[1] = {0};
        char *buffer = new char[sizeof(msgStruct)];

        msgStruct *data_struct = getMsgStructRef();

        while (true) {
            ready[0] = '\0';
            global_socket.recv(ready, (size_t) 1, 0);
            if (ready) {
                memcpy(buffer, data_struct, sizeof(msgStruct));
                global_socket.send(buffer, sizeof(msgStruct), 0);
            }
        }
    }

    std::thread initService() {
        global_socket.bind("tcp://*:5556");
        std::thread zmq_thread(
            repThread
        );
        zmq_thread.detach();
        return zmq_thread;
        // pthread_t listener_thread;
        // pthread_create(&listener_thread, NULL, repThread, NULL);
    }
}
#endif
