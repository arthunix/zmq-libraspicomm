#include <zmq.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <thread>
#include <sstream>
#include <string>

// #include "headers/msg_struct.h"
#include "headers/comms_img.hpp"

namespace comms {

    msgStruct *global_bss_struct = new msgStruct;

    zmq::context_t context(1);
    zmq::socket_t global_socket(context, zmq::socket_type::rep);

    msgStruct *getMsgStructRef() {
        // log("[getMsgStructRef] called");
        return global_bss_struct;
    }

    void repThread() {
        log("[repThread] listener thread initialized");
        char ready[1] = {0};
        char *buffer = new char[sizeof(msgStruct)];

        msgStruct *data_struct = getMsgStructRef();

        while (true) {
            ready[0] = '\0';
            // log("[repThread] waiting for 1 byte");
            global_socket.recv(ready, (size_t) 1, 0);
            // log("[repThread] rcvd 1 byte");
            if (ready) {
                memcpy(buffer, data_struct, sizeof(msgStruct));
                global_socket.send(buffer, sizeof(msgStruct), 0);
            } else {
                log("[WARNING][repThread] rcvd 1 NULL byte");
            }
        }
    }

    std::thread initService(unsigned port) {
        log("[initService] binding to %u", port);

        std::ostringstream oss;
        oss << "tcp://*:" << port;
        auto str = oss.str();

        log("[initComms] endpoint on: %s", str.c_str());
        global_socket.bind(str.c_str());
        log("[initService] bound to %u", port);
        std::thread zmq_thread(
            repThread
        );
        zmq_thread.detach();
        log("[initService] thread detached");
        return zmq_thread;
        // pthread_t listener_thread;
        // pthread_create(&listener_thread, NULL, repThread, NULL);
    }
}
