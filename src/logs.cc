#include <map>
#include <iterator>
#include "logs.h"
#include <iostream>
using namespace std;

void logs::add_maps(map<double,int> & dest, const map<double,int> & src){
  for(map<double,int>::const_iterator it = src.begin(); it != src.end(); it++)
    dest[it->first] += it->second;
  return;
}

logs logs::operator+(const logs & L){
  logs new_logs(this->filename, this->prec); ;
  new_logs.counter = this->counter + L.counter;

  add_maps(new_logs.logs_re, this->logs_re);
  add_maps(new_logs.logs_re, L.logs_re);

  add_maps(new_logs.logs_im, this->logs_im);
  add_maps(new_logs.logs_im, L.logs_im);

  add_maps(new_logs.logs_abs, this->logs_abs);
  add_maps(new_logs.logs_abs, L.logs_abs); 
  
  return new_logs; 
}

/* This is buggy and is not currently working */

logs logs::operator+=(const logs & L){
  logs new_logs(this->filename, this->prec);
  new_logs = this->operator+(L);
  return new_logs;
}

double logs::round(const double f){
  int approx = (int) (1/prec)*f;
  if(f - approx*prec < 0.5){
    return approx*prec;
  }else{
    return (approx+1)*prec;
  }
}

logs::logs(string name, double precision){
  filename = name;
  prec = precision; 
}

void logs::add(mpreal re, mpreal im){
  logs_re[round((double) re)]++;
  logs_im[round((double) im)]++;
  /* Might be somewhat slow */
  logs_abs[round((double) sqrt(re*re + im*im))]++; 
  counter++; 
}

unsigned long logs::size(){
  return counter; 
}

void logs::clear(){
  logs_re.clear();
  logs_im.clear();
  counter = 0; 
}

void logs::print(ofstream & file, const map<double,int> & m){
  for(map<double,int>::const_iterator it = m.begin(); it != m.end(); ++it)
    file << "g( " << it->first << ") = " << it->second << "\n";
}

void logs::dump(){
  ofstream file;

  file.open(filename, ofstream::out);

  if(!file){
    cerr << "Could not open " << filename << "\n";
    logs::clear();
    return; 
  }

  map<double,int> abs_value; 
  
  file << "Real part\n"
       << "---------------------------------------\n"; 

  print(file, logs_re); 

  file << "Imaginary part\n"
       << "---------------------------------------\n";

  print(file, logs_im); 

  file << "Absolute value\n"
       << "---------------------------------------\n";

  print(file, logs_abs); 
  
  file.close();
    
  logs::clear(); 
}




