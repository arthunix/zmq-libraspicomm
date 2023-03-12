#include <zmq.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>

// #include "headers/msg_struct.hpp"
#include "headers/comms_img.hpp"

namespace comms {

    zmq::context_t context(1);
    zmq::socket_t global_socket(context, zmq::socket_type::req);

    void initComms(char *ip, unsigned port) {
        // log("[initComms] called");

        std::ostringstream oss;
        oss << "tcp://" << ip << ":" << port;
        auto str = oss.str();

        log("[initComms] connection on: %s", str);
        global_socket.connect(str.c_str());
        log("[initComms] socket connected");
    }

    msgStruct getData() {
        // log("[getData] called");
        char req[2] = {'R', '\0'};
        // log("[getData] sending '%s'", req);
        global_socket.send(req, (size_t) 1, 0);

        char *buff = new char[sizeof(msgStruct)];
        // log("[getData] waiting for %u bytes", sizeof(msgStruct));
        global_socket.recv(buff, sizeof(msgStruct), 0);
        // log("[getData] rcvd %u bytes", sizeof(msgStruct));
        msgStruct *msg = new msgStruct;
        memcpy(msg, buff, sizeof(msgStruct));

        return *msg;
    }
}
