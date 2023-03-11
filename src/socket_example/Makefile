all: req rep

req: req.cpp
	g++ -ggdb req.cpp -o req -lzmq

rep: rep.cpp
	g++ -ggdb rep.cpp -o rep -lzmq

clean:
	rm rep req
