#include <zmq.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "src/headers/interRaspiComm.hpp"

struct msgStruct {
    float ang;
    float dist;
    float c;
    float d;
};

class Com {
public:
    zmq::socket_t responder;
    zmq::context_t context;
    int count;

    Com()
    : context(1)
    , responder(context, zmq::socket_type::rep)
    {
        this->count = 0;
        printf("binding...\n");
        responder.bind("tcp://127.0.0.1:5555");
        printf("bound\n");
    }

    void rcv() {
        char request[5];
        this->responder.recv(request, (size_t) 5, 0);
        printf("rcvd\n");
    }
};

// todo: voltar pro normal e fzer estilo C usando a lib C++:
// ter o socket global, um header e a thread usa o bss

int main () {
    // //  Prepare our context and socket
    // zmq::context_t context(2);

    Com commsa;
    commsa.rcv();
    // zmq::socket_t *responder;
    // zmq::socket_t responder(context, zmq::socket_type::rep);
    // responder(context, zmq::socket_type::rep);
    // responder.bind("tcp://*:5559");

    // RaspiComm comms = RaspiComm(IMG_PROCESSING);
    // comms.initService("localhost", 5555);

    while (true) {
        char request[5];
        // commsa.responder.recv(request, (size_t) 5, 0);
        // std::cout << "Received " << request << std::endl;
        commsa.rcv();
        msgStruct *msg = new msgStruct;
        msg->ang = 5.5f;
        char *reply = new char[sizeof(msgStruct)];
        memcpy(reply, msg, sizeof(msgStruct));
        free(msg);
        free(reply);
        // commsa.responder.send(reply, sizeof(msgStruct), 0);
    }
    return 0;
}
