CXX := $(CROSS_COMPILE)g++
CXXFLAGS += -Wall -g -fPIC -DNDEBUG -std=c++11 -Iinclude -Iparcel -Iril

objects := $(patsubst %.cpp, %.o, $(wildcard *.cpp))
objects += $(patsubst %.cpp, %.o, $(wildcard parcel/*.cpp))

rilc: clean $(objects)
	$(CXX) -o $@ $(objects) -pthread

clean:
	rm -rf rilc *.o parcel/*.o
