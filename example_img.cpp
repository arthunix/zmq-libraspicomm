#include "src/headers/interRaspiComm.hpp"
#include <cstdlib>

int main(int argc, char const *argv[]) {

    RaspiComm::msgStruct *data;

    data.ang = 5.5f;
    data.dist = 9.f;

    RaspiComm comm = RaspiComm(RaspiComm::IMG_PROCESSING);

    comm.initService(data);

    while (true) {
        sleep(3);
        data.ang = rand() % 45;

        comm.setStructVal(data);
        printf("sent data.ang=%.2f\n", data.ang);
    }

    return 0;
}
