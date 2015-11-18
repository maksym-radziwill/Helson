#include <map>
#include "mpreal.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std; 
using namespace mpfr;

class logs {
  double prec; 
  map<double, int> logs_re;
  map<double, int> logs_im;
  map<double, int> logs_abs; 
  unsigned long counter = 0;
  string filename; 
  double round(double); 
  void add_maps(map<double,int> &, const map<double,int> &); 
  void print(ofstream &, const map<double,int> &);
 public:
  logs(string, double); 
  logs operator+(const logs &);
  logs operator+=(const logs &); 
  void add(mpreal, mpreal);
  void dump();
  void tex(); 
  void clear(); 
  unsigned long size();
};

