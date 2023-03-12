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

namespace comms {

    zmq::context_t context(1);
    zmq::socket_t global_socket(context, zmq::socket_type::req);

    struct msgStruct {
        float ang;
        float dist;
        float c;
        float d;
    };

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

    msgStruct getData();
}
#endif
