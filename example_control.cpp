#include "src/headers/interRaspiComm.hpp"
#include <cstdlib>

int main(int argc, char const *argv[]) {

    RaspiComm::msgStruct data = {0};

    RaspiComm comm = RaspiComm(RaspiComm::CONTROL);

    comm.initService((const char *) "localhost", (unsigned int) 5556);

    while (true) {
        data = comm.getStruct();
        printf("got data.ang=%.2f\n", data.ang);
    }

    return 0;
}
