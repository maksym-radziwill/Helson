#include "helson.h"
using namespace std; 
/* Testing */
/* Display the seq array */
void RMF::output_seq(){
  for(i = seq.begin(); i != seq.end(); i++){
    cout << "seq[" << i - seq.begin() << "]: ";
    for(j = i->begin(); j != i->end(); j++){
      cout << *j << " ";
    }
    cout << "\n"; 
  }   
}

/* Testing */
/* Display the primes array */
void RMF::output_primes(){
  for(j = primes.begin(); j != primes.end(); j++)
    cout << "primes[" << j - primes.begin() << "]: " << *j << "\n";
}


/* Testing */
/* Display the val array */

void RMF::output_val(){

  for(j = primes.begin(); j != primes.end(); j++)
    cout << "val[" << *j << "] = " << val.at(*j) << "\n"; 
}

void RMF::output_cos_sin(){
  for(int i = 0; i < seed; i++){
    cout << i << " " << (cos_val)[i] << " " << (sin_val)[i] << "\n"; 
  }
}



  
