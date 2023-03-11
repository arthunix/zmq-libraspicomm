#include "src/headers/interRaspiComm.hpp"
#include <cstdlib>

int main(int argc, char const *argv[]) {

    RaspiComm::msgStruct data = {0};

    RaspiComm comm = RaspiComm(RaspiComm::CONTROL);

    comm.initService("localhost");

    while (true) {
        printf("sent data.ang=%.2f\n", data.ang);
        data.ang = rand() % 45;

        data = comm.getStruct();
    }

    return 0;
}
