#include <exception>
#include <cstdio>
#include <iostream>
#include <czmq.h>
#include <thread>

#include "headers/interRaspiComm.hpp"
#include "headers/utils.hpp"


RaspiComm::RaspiComm(unsigned short endType) {
    this->logger = utils::Logger("RaspiComm", "RaspiComm.log", utils::Logger::Info);
    this->logger.info("RaspiComm Obj Created");

    this->endType = endType;
}

RaspiComm::~RaspiComm() {
    free(this->sharedThreadStruct);

    if (this->endType == RaspiComm::IMG_PROCESSING) {
        zsock_destroy(&responder);
    } else if (this->endType == RaspiComm::CONTROL) {
        zsock_destroy(&requester);
    }
}

void RaspiComm::checkCommEndType(unsigned short neededEndType) {
    if (this->endType != neededEndType) {
        this->logger.error(
            "wrong comm end type: need %ud, is %ud",
            neededEndType,
            this->endType
        );

        throw std::exception();
    }
}

void RaspiComm::setStructVal(RaspiComm::msgStruct msg) {
    this->checkCommEndType(RaspiComm::IMG_PROCESSING);
    memcpy(this->sharedThreadStruct, &msg, sizeof(msgStruct));
    this->logger.info("shared thread mem struct updated");
}

void RaspiComm::initService(char *endpointIp, unsigned int port=DEFAULT_ZSOCKET_PORT) {
    if (this->endType == RaspiComm::IMG_PROCESSING) {
        this->checkCommEndType(RaspiComm::IMG_PROCESSING);
        this->logger.info("initService called - IMG_PROCESSING - REP");

        this->responder = zsock_new(ZMQ_REP);
        char endpoint[ENDPOINT_STR_MAX_LEN] = {0};
        sprintf(
            endpoint,
            "%s://*:%d",
            DEFAULT_CONN_PROTOCOL,
            port
        );
        int rc = zsock_bind(responder, endpoint);
        if (rc != port) {
            this->logger.error("Could not bind to port %d", port);
            throw std::exception();
        }

    } else if (this->endType == RaspiComm::CONTROL) {
        this->checkCommEndType(RaspiComm::CONTROL);
        this->logger.info("initService called - CONTROL - REQ");

        this->requester = zsock_new(ZMQ_REQ);
        // char *endpoint[ENDPOINT_STR_MAX_LEN] = {0};
        char endpoint[ENDPOINT_STR_MAX_LEN] = {0};
        sprintf(
            endpoint,
            "%s://%s:%d",
            DEFAULT_CONN_PROTOCOL,
            endpointIp,
            port
        );
        zsock_connect(requester, endpoint);

        // std::thread zmq_thread(
        //     RaspiComm::hangingZmqThread,
        //     &this->sharedThreadStruct,
        //     &this->responder,
        //     &this->logger
        // );
        std::thread zmq_thread(
            RaspiComm::hangingZmqThread,
            this
        );
    }
}

void RaspiComm::initService(RaspiComm::msgStruct firstMsg, char *endpointIp, unsigned int port=DEFAULT_ZSOCKET_PORT) {
    this->setStructVal(firstMsg);

    this->initService(endpointIp, port);
}

// void RaspiComm::hangingZmqThread(RaspiComm::msgStruct *msg, zsock_t *responder, utils::Logger logger) {
void RaspiComm::hangingZmqThread(RaspiComm::msgStruct *msg) {
    // logger = utils::Logger("ZMQthread", "RaspiComm.log", utils::Logger::Info)
    this->checkCommEndType(RaspiComm::IMG_PROCESSING);
    this->logger.info("initializing zmqThread");

    char ready;
    char buffer[sizeof(RaspiComm::msgStruct)];

    while (true) {
        ready = '\0';
        zmq_recv(this->responder, &ready, 1, 0);
        if (ready) {
            memcpy(buffer, &msg, sizeof(RaspiComm::msgStruct));
            zmq_send(this->responder, buffer, sizeof(RaspiComm::msgStruct), 0);
            logger.info("msg sent to requester");
        }
    }
}

RaspiComm::msgStruct RaspiComm::getStruct() {
    this->checkCommEndType(RaspiComm::CONTROL);
    // char *buffer[sizeof(RaspiComm::msgStruct)] = {0};
    zstr_send(requester, DEAFULT_REQ_MSG);
    char *buffer = zstr_recv(requester);

    RaspiComm::msgStruct *rcvdMsg;
    memcpy((void *)rcvdMsg, buffer, sizeof(RaspiComm::msgStruct));

    return *rcvdMsg;
}
