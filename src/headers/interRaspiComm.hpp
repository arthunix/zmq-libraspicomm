#ifndef INTER_RASPI_COMM_HPP
#define INTER_RASPI_COMM_HPP

#include <thread>

#include <czmq.h>

#include "utils.hpp"


#define DEFAULT_ZSOCKET_PORT                             5555;
#define DEFAULT_CONN_PROTOCOL                           "tcp";
#define ENDPOINT_STR_MAX_LEN                              100;


class RaspiComm {
    enum CommType : unsigned short {CONTROL = 0, IMG_PROCESSING};

    struct msgStruct {
        float ang;
        float dist;
        float c;
        float d;
    };


private:
    utils::Logger logger;
    unsigned short endType;
    msgStruct *sharedThreadStruct;
    std::string endpointIp;
    zsock_t *requester;
    void *responder;

    void hangingZmqThread(RaspiComm::msgStruct *msg);
    void checkCommEndType(unsigned short neededEndType);

public:
    RaspiComm(unsigned short endType);
    ~RaspiComm();

    void setStructVal(RaspiComm::msgStruct msg);
    void initService(char *endpointIp, unsigned int port);
    void initService(RaspiComm::msgStruct *firstMsg, unsigned int port);
    msgStruct getStruct();

};

#endif
