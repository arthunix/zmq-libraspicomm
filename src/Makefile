CC = g++
CXXFLAGS = -std=c++17 -Wall -static-libstdc++ -static-libgcc -Wwrite-strings -g -lm -lzmq -pthread

all: examples

examples: example_control example_img benchmark

example_img: example_img.cpp comms_img.cpp
	$(CC) comms_img.cpp example_img.cpp -o example_img $(CXXFLAGS)

example_control: example_control.cpp comms_control.cpp
	$(CC) comms_control.cpp example_control.cpp -o example_control $(CXXFLAGS)

benchmark: benchmark.cpp comms_control.cpp
	$(CC) benchmark.cpp example_control.cpp -o benchmark $(CXXFLAGS)
