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
