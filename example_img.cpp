#include "src/headers/interRaspiComm.hpp"
#include <cstdlib>
#include <unistd.h>

int main(int argc, char const *argv[]) {

    RaspiComm::msgStruct data;

    data.ang = 5.5f;
    data.dist = 9.f;

    RaspiComm comm = RaspiComm(RaspiComm::IMG_PROCESSING);

    comm.initService(data, (const char *) "localhost", (unsigned int) 5556);

    while (true) {
        sleep(3);
        data.ang = 3.3;

        comm.setStructVal(data);
        printf("sent data.ang=%.2f\n", data.ang);
    }

    return 0;
}
