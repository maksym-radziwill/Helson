#include "helson.h"
#include "rule.h"
#include "random.h"
#include "thread.h"
#include "logs.h"
#include <mutex>

using namespace std; 

/* Threads and their shared data */

mutex mu; 
extern vector<mpreal> results;
extern void log_add(int, mpreal, mpreal); 

logs Master_Log("helson.out", 0.01); 

void work(const int tid, const int len,
	  const int seed, const int highest_moment,
	  const int iterations, const int loging){

  vector<mpreal> sum (highest_moment);

  mpreal s = sqrt(support(len));

  RMF rmf(len, seed, rule, random_func, 0, tid);

  logs Logs ("helson.out",0.01); 
  
  results.resize(highest_moment);

  for(int i = 0; i < iterations ; i++){
    rmf.randomize();
    rmf.evaluate();
    
    for(int j = 0; j < highest_moment; j++)
      sum.at(j) += mpfr::pow(sqrt(rmf.re*rmf.re + rmf.im*rmf.im) / s, j+1); 

    if(loging)
      Logs.add(rmf.re / s, rmf.im / s);
    
  }
  
  mu.lock();
  
  for(int j = 0; j < highest_moment; j++){
    results.at(j) += sum.at(j) / iterations; 
    cout << "Thread " << tid << ", Moment " << j + 1 << " : " << sum.at(j) / iterations << "\n"; 
  }

  if(loging)
    Master_Log = Master_Log + Logs;
  
  mu.unlock();
  
}
