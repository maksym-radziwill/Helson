# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -Ofast -funroll-all-loops -std=c++11 -fomit-frame-pointer -ftree-loop-if-convert -ftree-loop-if-convert-stores -ftree-loop-distribution -ftree-parallelize-loops=16 -fprofile-use -fstrict-aliasing
CXX_FAST_FLAGS = -Wall -Ofast -std=c++11 -funroll-all-loops -fomit-frame-pointer -ftree-loop-if-convert -ftree-loop-if-convert-stores -ftree-loop-distribution -ftree-parallelize-loops=16 -fstrict-aliasing 
LIB = -lmpfr -lgmp -pthread
STATIC_LIB = -Wl,--whole-archive -lgmp -lmpfr -lpthread -Wl,--no-whole-archive -static

# ****************************************************

helson: main.o helson.o testing.o factors.o rule.o thread.o random.o logs.o
	$(CXX) $(CXXFLAGS) $(LIB) -o helson main.o helson.o testing.o factors.o rule.o thread.o random.o logs.o

static: main_static.o helson_static.o testing_static.o factors_static.o rule_static.o thread_static.o rule_static.o random_static.o logs_static.o
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -o static main.o helson.o testing.o factors.o rule.o thread.o random.o logs.o
	strip static

debug: main.o helson.o testing.o factors.o rule.o thread.o
	$(CXX) $(CXXFLAGS) $(LIB) -pg -o debug main.o helson.o testing.o factors.o rule.o

logs_static.o: logs.cc
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c logs.cc

logs.o: logs.cc
	$(CXX) $(CXXFLAGS) $(LIB) -c logs.cc

random_static.o: random.cc
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c random.cc

random.o: random.cc 
	$(CXX) $(CXXFLAGS) -c random.cc

thread_static.o: thread.cc
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c thread.cc

thread.o: thread.cc helson.h
	$(CXX) $(CXXFLAGS) -c thread.cc

main.o: main.cc helson.h
	$(CXX) $(CXXFLAGS) -c main.cc

rule_static.o: rule.cc 
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c rule.cc

rule.o: rule.cc
	$(CXX) $(CXXFLAGS) -c rule.cc

main_static.o: main.cc helson.h
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c main.cc

helson.o: helson.cc helson.h
	$(CXX) $(CXXFLAGS) -c helson.cc

helson_static.o: helson.cc helson.h
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c helson.cc

testing.o: testing.cc helson.h
	$(CXX) $(CXXFLAGS) -c testing.cc

testing_static.o: testing.cc helson.h
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c testing.cc

factors.o: factors.cc helson.h
	$(CXX) $(CXXFLAGS) -c factors.cc

factors_static.o: factors.cc helson.h
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c factors.cc

example: 
	g++ main.cc helson.cc testing.cc factors.cc -lmpfr -lgmp -std=c++11 -O2 -pthread

clean:
	rm -f *.o 
	rm static
	rm debug
	rm helson

