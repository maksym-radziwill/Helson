#include "helson.h"

using namespace std;
using namespace mpfr; 

void RMF::randomize(){
  for(j = primes.begin(); j != primes.end(); j++)
    val.at(*j) = random_seed(seed,thread_id);
}

void RMF::evaluate(){
  /* This is the slow part */

  re = 0;
  im = 0; 

  for(int j = 0; j < seed; j++) freq.at(j) = 0; 

  /* Evaluate frequency of occurence of a given angle */
  /* Store the result in freq[sum] */
  
  unsigned long sum = 0;
  for(i = seq.begin(); i != seq.end(); i++){
    for(j = i->begin(); j != i->end(); j++){
      sum += val.at(*j) % seed;
    }
    
    freq.at(sum % seed) += 1;
    sum = 0;
  }

  /* Compute the results */

  for(int i = 0; i < seed; i++){
    re += freq.at(i)*cos_val.at(i);
    im += freq.at(i)*sin_val.at(i);
  }
}

RMF::RMF(int length, int init_seed, bool (*f)(int,int), unsigned long (*g)(unsigned long,int), int r_seed, int tid){
  random_seed = g; 
  support_rule = f;
  len = length;
  seed = init_seed;
  rseed = r_seed;
  thread_id = tid; 
  

  /* Setup MPFR */

  const int digits = 5;
  mpreal::set_default_prec(digits2bits(digits));
  pi = const_pi();
  for(int i = 0; i < seed; i++){
    mpreal ratio = i;
    ratio = i / (mpreal) seed; 
    cos_val.push_back(mpfr::cos(2*pi*ratio));
    sin_val.push_back(mpfr::sin(2*pi*ratio)); 
  }
  
  /* Setup buffers */

  freq.resize(seed+1);
  val.resize(length+1); 
  primes.reserve(length+1); 
  seq.reserve(length+1); 
  
  /* Input factorizations into "seq" */
  /* Input primes into "primes" */

  for(int i = 2; i < len; i++){
    vector<int> factors; 
    factorize(factors, i);
    if(support_rule(i,len))        seq.push_back(factors);
    if(factors.size() == 1) primes.push_back(*factors.begin()); 
  }

}

