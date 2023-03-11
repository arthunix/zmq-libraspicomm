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

void RaspiComm::initService(const char *endpointIp, unsigned int port) {
    if (this->endType == RaspiComm::IMG_PROCESSING) {
        this->checkCommEndType(RaspiComm::IMG_PROCESSING);
        this->logger.info("initService called - IMG_PROCESSING - REP");

        // zmq::context_t context(2);
        // this->responder = zmq::socket_t(context, zmq::socket_type::rep);
        zmq::context_t context(2);
        this->responder(context, zmq::socket_type::rep);

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

        // zmq::context_t context(1);
        // this->requester = socket(context, zmq::socket_type::req);
        zmq::context_t context (1);
        this->requester = zmq::socket_t(context, zmq::socket_type::req);

        char endpoint[ENDPOINT_STR_MAX_LEN] = {0};
        sprintf(
            endpoint,
            "%s://%s:%d",
            DEFAULT_CONN_PROTOCOL,
            endpointIp,
            port
        );
        this->requester.connect(endpoint);
    }
}
