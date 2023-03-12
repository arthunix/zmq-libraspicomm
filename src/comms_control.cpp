#include <zmq.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "headers/msg_struct.h"
#include "headers/comms_img.hpp"
#include "headers/utils.hpp"

namespace comms {

    zmq::context_t context(1);
    zmq::socket_t global_socket(context, zmq::socket_type::req);
    utils::Logger comms_logger("ControlComms", "ControlComms.log", utils::Logger::Info);

    void initComms() {
        comms_logger.info("[initComms] called");
        global_socket.connect("tcp://localhost:5556");
        comms_logger.info("[initComms] socket connected");
    }

    msgStruct getData() {
        comms_logger.info("[getData] called");
        char req[2] = {'R', '\0'};
        comms_logger.info("[getData] sending '%s'", req);
        global_socket.send(req, (size_t) 1, 0);

        char *buff = new char[sizeof(msgStruct)];
        comms_logger.info("[getData] waiting for %u bytes", sizeof(msgStruct));
        global_socket.recv(buff, sizeof(msgStruct), 0);
        comms_logger.info("[getData] rcvd %u bytes", sizeof(msgStruct));
        msgStruct *msg = new msgStruct;
        memcpy(msg, buff, sizeof(msgStruct));

        return *msg;
    }
}
