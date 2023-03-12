CC = g++
CXXFLAGS = -std=c++17 -Wall -static-libstdc++ -static-libgcc -Wwrite-strings -g -lm -lczmq -pthread

all: control img

control: control.cpp
	g++ -ggdb control.cpp -o control -lzmq -pthread

img: img.cpp
	g++ -ggdb img.cpp -o img -lzmq -pthread

clean:
	rm img control
