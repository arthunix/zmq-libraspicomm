//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

struct msgStruct {
    float ang;
    float dist;
    float c;
    float d;
};


int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket(context, zmq::socket_type::req);

    std::cout << "Connecting to REP..." << std::endl;
    socket.connect("tcp://localhost:5559");

    char buff[5];
    memcpy(buff, "Hello", 5);
    std::cout << "Sending " << buff << std::endl;
    socket.send(buff, (size_t) 5, 0);

    char *reply = new char[sizeof(msgStruct)];
    socket.recv(reply, sizeof(msgStruct), 0);
    msgStruct *msg = new msgStruct;
    memcpy(msg, reply, sizeof(msgStruct));
    std::cout << "Received " << msg->ang << std::endl;

    return 0;
}
