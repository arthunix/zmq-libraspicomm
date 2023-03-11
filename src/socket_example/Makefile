all: req rep

# req: req.cpp
# 	g++ -ggdb req.cpp src/interRaspiComm.cpp -o req -lzmq -pthread
#
# rep: rep.cpp
# 	g++ -ggdb rep.cpp src/interRaspiComm.cpp -o rep -lzmq -pthread

req: req.cpp
	g++ -ggdb req.cpp -o req -lzmq -pthread

rep: rep.cpp
	g++ -ggdb rep.cpp -o rep -lzmq -pthread

clean:
	rm rep req
