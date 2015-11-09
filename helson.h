#include "mpreal.h"
#include "factors.h"
#include <iostream>
#include <gmpxx.h>
#include <vector>
#include <algorithm>

#define MAX_THREADS 512
using namespace std;
using namespace mpfr;


class RMF {
  mpreal pi;
  
  int len, seed;
 
  vector<int> primes, val, freq;
  vector<int>::iterator j;
  
  vector<vector<int> > seq; 
  vector<vector<int> >::iterator i; 
  
  unsigned long (*random_seed)(unsigned long); 
  bool (*support_rule)(int,int); 

  vector<mpreal> sin_val, cos_val;
  
 public:
  
  mpreal re = 0;
  mpreal im = 0;

  RMF(int, int, bool (*f)(int,int), unsigned long (*g)(unsigned long));
  void randomize();
  void evaluate();
  
  /* Testing */

  void output_primes();
  void output_cos_sin();
  void output_val(); 
  void output_seq(); 
};
