#include "mpreal.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std; 
using namespace mpfr;

class logs {
  union double_binary { char arr[8];  double d; };
  vector <double> logs_re;
  vector <double> logs_im;
  unsigned long counter = 0;
  string filename; 
 public:
  logs(string); 
  void add(mpreal, mpreal);
  void dump();
  void clear(); 
  unsigned long size();
};
