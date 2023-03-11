#include <zmq.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

#ifndef _WIN32
    #include <unistd.h>
#else
    #include <windows.h>
    #define sleep(n)	Sleep(n)
#endif

struct msgStruct {
    float ang;
    float dist;
    float c;
    float d;
};


int main () {
    //  Prepare our context and socket
    zmq::context_t context (2);
    zmq::socket_t socket(context, zmq::socket_type::rep);
    socket.bind("tcp://*:5559");

    while (true) {
        char request[5];
        socket.recv(request, (size_t) 5, 0);
        std::cout << "Received " << request << std::endl;

        msgStruct *msg = new msgStruct;
        msg->ang = 5.5f;
        char *reply = new char[sizeof(msgStruct)];
        memcpy(reply, msg, sizeof(msgStruct));
        socket.send(reply, sizeof(msgStruct), 0);
    }
    return 0;
}
