# RaspiComms

To install correct version of zmq lib, run:

#### Install dependencies:

```sh
#if debian/ubuntu
sudo apt update -y && sudo apt upgrade -y
sudo apt install libzmq3-dev git -y

#if athoner unix
wget https://github.com/zeromq/libzmq/releases/download/v4.3.4/zeromq-4.3.4.tar.gz
cd zeromq-4.3.4/
CXXFLAGS=-Wno-error ./configure
make
sudo make install
cd ..
```

#### Clone repository:
```sh
git clone git@github.com:LombardiDaniel/RaspiComms.git
cd RaspiComms
make
```

#### Example of Code:
```C++
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "headers/comms_control.hpp"

#define COMMS_DEBUG 1

int main (int argc, char const *argv[])
{

    comms::initComms("localhost", 5556);
    std::cout << "connected" << '\n';
    while (true) {
        comms::msgStruct msg = comms::getData();
        std::cout << msg.ang << '\n';
        sleep(1);
    }

    return 0;
}
```

```C++
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "headers/comms_img.hpp"

#define COMMS_DEBUG 1

int main (int argc, char const *argv[])
{

    comms::initService(5556);
    comms::msgStruct *msg = new comms::msgStruct;
    msg = comms::getMsgStructRef();
    while (true) { // codigo de raspi img
        msg->ang = 5.5;
    }

    return 0;
}
```
