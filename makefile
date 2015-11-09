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
	$(CXX) $(CXXFLAGS) $(LIB) -o helson obj/main.o obj/helson.o obj/testing.o obj/factors.o obj/rule.o obj/thread.o obj/random.o obj/logs.o

static: main_static.o helson_static.o testing_static.o factors_static.o rule_static.o thread_static.o rule_static.o random_static.o logs_static.o
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -o static obj/main.o obj/helson.o obj/testing.o obj/factors.o obj/rule.o obj/thread.o obj/random.o obj/logs.o
	strip static

debug: main.o helson.o testing.o factors.o rule.o thread.o
	$(CXX) $(CXXFLAGS) $(LIB) -pg -o debug obj/main.o obj/helson.o obj/testing.o obj/factors.o obj/rule.o

logs_static.o: src/logs.cc
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c src/logs.cc -o obj/logs.o

logs.o: src/logs.cc
	$(CXX) $(CXXFLAGS) $(LIB) -c src/logs.cc -o obj/logs.o

random_static.o: src/random.cc
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c src/random.cc -o obj/random.o

random.o: src/random.cc 
	$(CXX) $(CXXFLAGS) -c src/random.cc -o obj/random.o

thread_static.o: src/thread.cc
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c src/thread.cc -o obj/thread.o

thread.o: src/thread.cc src/helson.h
	$(CXX) $(CXXFLAGS) -c src/thread.cc -o obj/thread.o

main.o: src/main.cc src/helson.h
	$(CXX) $(CXXFLAGS) -c src/main.cc -o obj/main.o

rule_static.o: src/rule.cc 
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c src/rule.cc -o obj/rule.o

rule.o: src/rule.cc
	$(CXX) $(CXXFLAGS) -c src/rule.cc -o obj/rule.o

main_static.o: src/main.cc src/helson.h
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c src/main.cc -o obj/main.o

helson.o: src/helson.cc src/helson.h
	$(CXX) $(CXXFLAGS) -c src/helson.cc -o obj/helson.o

helson_static.o: src/helson.cc src/helson.h
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c src/helson.cc -o obj/helson.o

testing.o: src/testing.cc src/helson.h
	$(CXX) $(CXXFLAGS) -c src/testing.cc -o obj/testing.o

testing_static.o: src/testing.cc src/helson.h
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c src/testing.cc -o obj/testing.o

factors.o: src/factors.cc src/helson.h
	$(CXX) $(CXXFLAGS) -c src/factors.cc -o obj/factors.o

factors_static.o: src/factors.cc src/helson.h
	$(CXX) $(CXX_FAST_FLAGS) $(STATIC_LIB) -c src/factors.cc -o obj/factors.o

clean:
	rm -f obj/*.o 
	rm static
	rm debug
	rm helson

