all: example_control example_img interRaspiComm

example_control: example_control.cpp
	g++ example_control.cpp -c -lzmq -pthread

example_img: example_img.cpp
	g++ example_img.cpp -c -lzmq -pthread

interRaspiComm: src/interRaspiComm.cpp
	g++ src/interRaspiComm.cpp -c -lzmq -pthread

control: example_control.cpp src/interRaspiComm.cpp
	g++ example_control.cpp src/interRaspiComm.cpp -o control.out -lzmq -pthread

img: example_img.cpp src/interRaspiComm.cpp
	g++ example_img.cpp src/interRaspiComm.cpp -o img.out -lzmq -pthread
