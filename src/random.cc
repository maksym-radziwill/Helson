#include <iostream>
#include <random>
#include "random.h"
using namespace std;

/* Source of randomness */

unsigned long (*random_func)(unsigned long); 

unsigned long srand_random(const unsigned long seed){
  static int init = 0;
  if(init == 0){
    srand(time(0));
    init = 1; 
  }
  
  return (rand() % seed);
}

unsigned long mersenne_random(const unsigned long seed){
  static int init = 0;
  static mt19937 mt(time(0)); 

  return mt() % seed; 
}
