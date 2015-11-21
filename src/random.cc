#include <iostream>
#include <random>
#include <fstream>
#include <map>
#include <thread>
#include <mutex>
#include "random.h"
using namespace std;

/* Source of randomness */

unsigned long (*random_func)(unsigned long, int); 

unsigned long return_seed(){
  char block[sizeof(unsigned long)]; 
  ifstream urandom("/dev/urandom", ios::in | ios::binary);
  urandom.read(block, sizeof(unsigned long)); 
  return (unsigned long) *block; 
}

unsigned long def_random(const unsigned long seed, const int thread){
  uniform_int_distribution<> d(1, seed);
  static vector<mt19937> random_map(max_thread);
  static vector<int> init(max_thread);
  
  if(init[thread] == 0){
    random_map[thread].seed(return_seed());
    init[thread] = 1; 
  }
  
  return d(random_map[thread]);
}

unsigned long srand_random(const unsigned long seed, int thread){
  static int init = 0;
  if(init == 0){
    srand(time(0));
    init = 1; 
  }
  
  return (rand() % seed);
}

unsigned long mersenne_random(const unsigned long seed, int random){
  static mt19937 mt(time(0)); 

  return mt() % seed; 
}
