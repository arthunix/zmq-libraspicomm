/*
MIT License

Copyright (c) 2023 Daniel Lombardi de Oliveira
Copyright (c) 2023 Arthur Eugenio Silverio

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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

        log("[initComms] connection on: %s", str.c_str());
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
