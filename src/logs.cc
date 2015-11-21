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
  int gaussian_gen = 0;
  double prec_gen = 0; 
  
  if(L.gaussian + this-> gaussian > 0)
    gaussian_gen = 1; 

  if(this->prec <= L.prec)
    prec_gen = this->prec;
  else
    prec_gen = L.prec; 
  
  logs new_logs(this->filename, prec_gen, gaussian_gen); ;
  new_logs.counter = this->counter + L.counter;

  add_maps(new_logs.logs_re, this->logs_re);
  add_maps(new_logs.logs_re, L.logs_re);

  add_maps(new_logs.logs_im, this->logs_im);
  add_maps(new_logs.logs_im, L.logs_im);

  add_maps(new_logs.logs_abs, this->logs_abs);
  add_maps(new_logs.logs_abs, L.logs_abs); 

  add_maps(new_logs.logs_gaussian, this->logs_gaussian);
  add_maps(new_logs.logs_gaussian, L.logs_gaussian);

  add_maps(new_logs.logs_gaussian_abs, this->logs_gaussian_abs);
  add_maps(new_logs.logs_gaussian_abs, L.logs_gaussian_abs); 
  
  return new_logs; 
}

/* This is buggy and is not currently working */

logs logs::operator+=(const logs & L){
  logs new_logs(this->filename, this->prec, this->gaussian);
  new_logs = this->operator+(L);
  return new_logs;
}

double logs::round(const double f){
  int approx = (int) (1/prec)*f;
  if(f - approx*prec < prec*0.5){
    return approx*prec;
  }else{
    return (approx+1)*prec;
  }
}

logs::logs(string name, double precision, int gauss){
  filename = name;
  prec = precision;
  gaussian = gauss; 
}

double logs::gen_gaussian(){
  static default_random_engine generator;
  /* The Gaussian approximating the real and imaginary part has variance 1/2 */
  normal_distribution<double> distribution(0.0,std::sqrt(0.5));
  return distribution(generator); 
}

double logs::gen_gaussian_abs(){
  static default_random_engine generator;
  normal_distribution<double> distribution(0.0,std::sqrt(0.5));
  double number_re = distribution(generator);
  double number_im = distribution(generator);
  return std::sqrt(number_re*number_re + number_im*number_im); 
}

void logs::add(mpreal re, mpreal im){
  logs_re[round((double) re)]++;
  logs_im[round((double) im)]++;
  /* Might be somewhat slow */
  logs_abs[round((double) sqrt(re*re + im*im))]++; 
 
  if(gaussian){
    logs_gaussian[round((double) gen_gaussian())]++;
    logs_gaussian_abs[round((double) gen_gaussian_abs())]++; 
  }

  counter++; 
}

unsigned long logs::size(){
  return counter; 
}

void logs::clear(){
  logs_re.clear();
  logs_im.clear();
  logs_gaussian.clear();
  logs_gaussian_abs.clear(); 
  counter = 0; 
}

void logs::print(ofstream & file, const map<double,int> & m){
  for(map<double,int>::const_iterator it = m.begin(); it != m.end(); ++it)
    file << "g( " << it->first << ") = " << it->second << "\n";
}

void logs::open_file(string filename, ofstream & file){ 
  file.open(filename, ofstream::out);

  if(!file){
    cerr << "Could not open " << filename << "\n";
  }
}

void logs::dump(){
  ofstream file;

  open_file(filename + ".re", file);
  if(file) print(file, logs_re); 
  file.close(); 
  
  open_file(filename + ".im", file);
  if(file) print(file, logs_im);
  file.close();

  open_file(filename + ".abs", file);
  if(file) print(file, logs_abs);
  file.close(); 

  if(gaussian){
    open_file(filename + ".normal", file);
    if(file) print(file, logs_gaussian);
    file.close();

    open_file(filename + ".normal.abs", file);
    if(file) print(file, logs_gaussian_abs);
    file.close(); 
  }
  
  logs::clear(); 
}




