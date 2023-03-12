CC = g++
CXXFLAGS = -std=c++17 -static-libstdc++ -static-libgcc -g -w -lm -lzmq -pthread

all: examples

examples: example_control example_img

example_img: example_img.cpp comms_img.cpp
	$(CC) comms_img.cpp example_img.cpp -o example_img $(CXXFLAGS)

example_control: example_control.cpp comms_control.cpp
	$(CC) comms_control.cpp example_control.cpp -o example_control $(CXXFLAGS)

benchmark: benchmark.cpp comms_control.cpp
	$(CC) comms_control.cpp benchmark.cpp -o benchmark $(CXXFLAGS)
