/* Check why in the case of primes we don't get Gaussian behavior?? */
/* Also Rademacher case is now messed up, because we draw the wrong Gaussian 
   to compare with, and also there is no reason to plot the complex Gaussian
   anymore */

/* Add an option to dump all the data to a file */
/* The data can be then later analyzed with some more efficient
   programming language or so */

/* Issue below is now fixed */
/* There is a problem here with the use of randomness in threads
   because each thread gets the same seed of randomness therefore
   weakining the final result of adding up */

#include "helson.h"
#include "random.h"
#include "rule.h"
#include "thread.h"
#include "logs.h"
#include <random>
#include <unistd.h>

using namespace std;

vector<mpreal> results;

extern logs Master_Log; 

inline void prepare_output(ostringstream & str, const int len,
		    const int sample, const int num_threads,
		    const int loging, const int prec,
		    const int gaussian_gen){

  if(loging)
    str << "Loging enabled\n";

  if(gaussian_gen)
    str << "Generated auxiliary Gaussian data\n";
  
  str << "Used " << num_threads << " threads\n"
      << "Summed up to " << len << "\n"
      << "Sampled " << sample << " times\n";

}

int main(int argc, char ** argv){

  if(argc < 2){
  usage:
    cout << "Usage: " << argv[0] << " length -t [num threads] -r [deg. root of unity] -R -L -i [num of iterations] -m [Moments] -G [Var] -P [precision]\n"
	 << "-R : Rademacher switch\n"
	 << "-t : number of threads\n"
	 << "-m : highest moment to compute\n"
	 << "-r : highest root of unity used in integral approximation\n"
	 << "-i : how many time more samples give the length\n"
	 << "-L : log switch -- logs to helson.log\n"
	 << "-G : Generate Gaussian random sample with variance Var\n"
	 << "-P : precision of logs\n"; 

    return 1; 
  }

  int len = atoi(argv[1]);
  int seed = std::sqrt(atoi(argv[1])); 
  int ITER = 20;
  int loging = 0;   
  int opt_char, highest_moment = 1; 
  int num_threads = 1; 
  double gaussian_var = 0; 
  double prec = 0.01; 
  
  //  rule = &prime_rule;
  //rule = &arith_rule; 
  rule = &default_rule; 
  //    rule = &smooth_rule; 
  
  //  random_func = &srand_random; 
  random_func = &def_random;
  
  while((opt_char = getopt(argc, argv, "t:s:Rm:r:hi:LG:P")) != EOF){
    switch(opt_char){
    case 'L': loging = 1; break;
    case 't': if(atoi(optarg) > 0) num_threads = atoi(optarg); break;
    case 'r': if(atoi(optarg) > 1) seed = atoi(optarg); break;
    case 'R': rule = &rademacher_rule; break;
    case 'm': if(atoi(optarg) > 0) highest_moment = atoi(optarg); break;
    case 'i': if(atoi(optarg) > 0) ITER = atoi(optarg); break;
    case 'G': if(atof(optarg) > 0) gaussian_var = atof(optarg); break;
    case 'P': if(atof(optarg) > 0) prec = atof(optarg); break; 
    case 'h': goto usage;
    case '?': goto usage; 
    }
  }
  
  thread t[num_threads]; 

  for(int i = 0; i < num_threads; ++i){
    t[i] = thread(work, i, len, seed, highest_moment, ITER * support(len) / num_threads, loging, prec, gaussian_var);
  }
    
  for(int i = 0; i < num_threads; ++i)
    t[i].join(); 

  /* --------------------------------------- */
  /* Output the result - Slightly hacky here */ 
  
  ostringstream out; 
  prepare_output(out, len, ITER*support(len), num_threads, loging, prec, gaussian_var); 
    
  for(int j = 0; j < highest_moment; j++){
    out << "Final result, moment " << (int) (j + 1) << " : " << (double) results.at(j) / num_threads << "\n"; 
  }

  cout << out.str(); 
  
  if(loging){
    Master_Log.dump();
    ofstream file ("helson.out");
    if(file){
      file << out.str();
      file.close();
    }
  }
  
  return 0; 
}
