#include "factors.h"
#include <iostream>
#include <algorithm>

bool (*rule)(int, int); 

int support(int len){
  int N = 0; 
  for(int i = 1; i < len; i++)
    if(rule(i,len)) N++;
  return N; 
}

bool smooth_rule(int n, int len){
  if(n == 1) return true;
  
  std::vector<int> factors;
  factorize(factors, n);
  if(*std::max_element(factors.begin(),factors.end()) > 20)
    return true; 
  else
    return false;
}

bool default_rule(int n, int len){
  return true; 
}

bool prime_rule(int n, int len){
  if(n == 1) return false;
  std::vector<int> factors;
  factorize(factors, n);
  if(factors.size() == 1)
    return true;
  else
    return false; 
}

bool rademacher_rule(int n, int len){
  if(n == 1) return true;
  
  std::vector<int> factors;
  factorize(factors, n);
  std::sort(factors.begin(), factors.end());
  for(std::vector<int>::iterator j = factors.begin(); j != (factors.end()); j++)
    if(*j == *(j+1)) return false;
  
  return true; 
}