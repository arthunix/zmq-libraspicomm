#include <zmq.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "headers/msg_struct.h"
#include "headers/comms_img.hpp"

namespace comms {

    zmq::context_t context(1);
    zmq::socket_t global_socket(context, zmq::socket_type::req);

    void initComms() {
        global_socket.connect("tcp://localhost:5556");
    }

    msgStruct getData() {

        char req[2] = {'R', '\0'};
        global_socket.send(req, (size_t) 1, 0);

        char *buff = new char[sizeof(msgStruct)];
        global_socket.recv(buff, sizeof(msgStruct), 0);
        msgStruct *msg = new msgStruct;
        memcpy(msg, buff, sizeof(msgStruct));

        return *msg;
    }
}
