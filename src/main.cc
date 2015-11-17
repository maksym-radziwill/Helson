/* Add an option to dump all the data to a file */
/* The data can be then later analyzed with some more efficient
   programming language or so */

/* There is a problem here with the use of randomness in threads
   because each thread gets the same seed of randomness therefore
   weakining the final result of adding up */

#include "helson.h"
#include "random.h"
#include "rule.h"
#include "thread.h"
#include <random>
#include <unistd.h>

using namespace std;

vector<mpreal> results;

static int num_threads = 1; 

int main(int argc, char ** argv){

  if(argc < 2){
  usage:
    cout << "Usage: " << argv[0] << " length -t [num threads] -r [deg. root of unity] -R -L -i [num of iterations] -m [Moments]\n"
	 << "-R : Rademacher switch\n"
	 << "-t : number of threads\n"
	 << "-m : highest moment to compute\n"
	 << "-r : highest root of unity used in integral approximation\n"
	 << "-i : how many time more samples give the length\n"
	 << "-L : log switch -- logs to helson.log\n";

    return 1; 
  }

  int len = atoi(argv[1]);
  int seed = std::sqrt(atoi(argv[1])); 
  int ITER = 20;
  int loging = 0;   
  int opt_char, highest_moment = 1; 
  
  //  rule = &prime_rule;
  rule = &default_rule; 

  //  random_func = &srand_random; 
  // mt19937 mt(time(0)); 
  random_func = &def_random;
  
  //  random_func = &mt;
  
  while((opt_char = getopt(argc, argv, "t:s:Rm:r:hi:L")) != EOF){
    switch(opt_char){
    case 'L': loging = 1; break;
    case 't': if(atoi(optarg) > 0) num_threads = atoi(optarg); break;
    case 'r': if(atoi(optarg) > 1) seed = atoi(optarg); break;
    case 'R': rule = &rademacher_rule; break;
    case 'm': if(atoi(optarg) > 0) highest_moment = atoi(optarg); break;
    case 'i': if(atoi(optarg) > 0) ITER = atoi(optarg); break;
    case 'h': goto usage;
    case '?': goto usage; 
    }
  }
  
  thread t[num_threads]; 

  for(int i = 0; i < num_threads; ++i){
    t[i] = thread(work, i, len, seed, highest_moment, ITER * support(len) / num_threads, loging);
  }
    
  for(int i = 0; i < num_threads; ++i)
    t[i].join(); 

  for(int j = 0; j < highest_moment; j++)
    cout << "Final result, moment " << j + 1 << " : " << (double) results.at(j) / num_threads<< "\n"; 

  return 0; 
}
