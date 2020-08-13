CXX := $(CROSS_COMPILE)g++
CXXFLAGS += -Wall -g -fPIC -std=c++11 -DNDEBUG -I./include -I./parcel

objects := $(patsubst %.cpp, %.o, $(wildcard *.cpp))
objects += $(patsubst %.cpp, %.o, $(wildcard parcel/*.cpp))

rilc: clean $(objects)
	$(CXX) -o $@ $(objects) -pthread

clean:
	rm -rf rilc *.o