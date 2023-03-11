#include <exception>
#include <cstdio>
#include <iostream>
#include <zmq.hpp>
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
        // zsock_destroy(&responder);
    } else if (this->endType == RaspiComm::CONTROL) {
        // zsock_destroy(&requester);
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

void RaspiComm::setStructVal(RaspiComm::msgStruct &msg) {
    this->checkCommEndType(RaspiComm::IMG_PROCESSING);
    memcpy(this->sharedThreadStruct, &msg, sizeof(msgStruct));
    this->logger.info("shared thread mem struct updated");
}

void RaspiComm::initService(const char *endpointIp, unsigned int port=DEFAULT_ZSOCKET_PORT) {
    if (this->endType == RaspiComm::IMG_PROCESSING) {
        this->checkCommEndType(RaspiComm::IMG_PROCESSING);
        this->logger.info("initService called - IMG_PROCESSING - REP");

        zmq::context_t context(2);
        this->responder = (zmq::socket_t) socket(context, zmq::socket_type::rep);
        char endpoint[ENDPOINT_STR_MAX_LEN] = {0};
        sprintf(
            endpoint,
            "%s://*:%d",
            DEFAULT_CONN_PROTOCOL,
            port
        );
        this->responder.bind(endpoint);

    } else if (this->endType == RaspiComm::CONTROL) {
        this->checkCommEndType(RaspiComm::CONTROL);
        this->logger.info("initService called - CONTROL - REQ");

        zmq::context_t context(1);
        this->requester = (zmq::socket_t) socket(context, zmq::socket_type::req);
        // char *endpoint[ENDPOINT_STR_MAX_LEN] = {0};
        char endpoint[ENDPOINT_STR_MAX_LEN] = {0};
        sprintf(
            endpoint,
            "%s://%s:%d",
            DEFAULT_CONN_PROTOCOL,
            endpointIp,
            port
        );
        requester.connect(endpoint);

        std::thread zmq_thread(
            RaspiComm::hangingZmqThread,
            std::ref(this->sharedThreadStruct),
            std::ref(this->responder)
            // std::ref(this->logger)
        );
    }
}

void RaspiComm::initService(RaspiComm::msgStruct &firstMsg, const char *endpointIp, unsigned int port=DEFAULT_ZSOCKET_PORT) {
    this->setStructVal(firstMsg);

    this->initService(endpointIp, port);
}

// void RaspiComm::hangingZmqThread(RaspiComm::msgStruct *msg, zsock_t *responder, utils::Logger *logger) {
void RaspiComm::hangingZmqThread(RaspiComm::msgStruct *msg, zsock_t *responder) {
// void RaspiComm::hangingZmqThread(RaspiComm::msgStruct *msg) {
    // logger = utils::Logger("ZMQthread", "RaspiComm.log", utils::Logger::Info)
    // this->checkCommEndType(RaspiComm::IMG_PROCESSING);
    // logger.info("initializing zmqThread");

    char *ready = new char;
    char *buffer = new char[sizeof(RaspiComm::msgStruct)];

    while (true) {
        ready = '\0';
        responder->recv(ready, (size_t) 1, 0);
        if (ready) {
            memcpy(buffer, msg, sizeof(RaspiComm::msgStruct));
            responder->send(buffer, sizeof(RaspiComm::msgStruct), 0);
            // logger.info("msg sent to requester");
        }
    }
}

RaspiComm::msgStruct RaspiComm::getStruct() {
    this->checkCommEndType(RaspiComm::CONTROL);
    // char *buffer[sizeof(RaspiComm::msgStruct)] = {0};
    char outBuffer[1] = {DEAFULT_REQ_MSG};
    socker.send(outBuffer, (size_t) 1, 0);

    // char *inBuffer = (char *) malloc(sizeof(RaspiComm::msgStruct));
    char *inBuffer = new char[sizeof(RaspiComm::msgStruct)];
    RaspiComm::msgStruct *rcvdMsg = new msgStruct;

    this->requester.recv(inBuffer, sizeof(RaspiComm::msgStruct), 0);
    memcpy(rcvdMsg, inBuffer, sizeof(RaspiComm::msgStruct));

    return *rcvdMsg;
}
