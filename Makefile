CXX=g++
CXXFLAGS=-std=c++11

NN_FILE=NearestNeighbor.cpp
RD_FILE=RandData.cpp
NN_BIN=closestPair
RD_BIN=randData


all: closestPair randData

closestPair: $(NN_FILE)
	$(CXX) $(CXXFLAGS) -o $(NN_BIN) $(NN_FILE)

randData: $(RD_FILE)
	$(CXX) $(CXXFLAGS) -o $(RD_BIN) $(RD_FILE)

clean:
	rm -f *.o
	rm $(NN_BIN)
	rm $(RD_BIN)
