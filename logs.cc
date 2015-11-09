#include "logs.h"
#include <iostream>
using namespace std;

logs::logs(string name){
  filename = name; 
}

void logs::add(mpreal re, mpreal im){
  logs_re.push_back((double) re);
  logs_im.push_back((double) im);
  counter++; 
}

unsigned long logs::size(){
  return counter; 
}

void logs::clear(){
  logs_re.resize(0);
  logs_im.resize(0);
  counter = 0; 
}

void logs::dump(){
  ofstream file;

  file.open(filename, ofstream::out);

  if(!file){
    cerr << "Could not open " << filename << "\n";
    logs::clear();
    return; 
  }
  
  for(unsigned long i = 0; i < counter; i++){
    union double_binary binary;
    binary.d = logs_re.at(i);
    for(int j = 0; j < 8; j++)
      file << binary.arr[j];
    binary.d = logs_im.at(i);
    for(int j = 0; j < 8; j++)
      file << binary.arr[j]; 
  }
  file.close();
    
  logs::clear(); 
}




