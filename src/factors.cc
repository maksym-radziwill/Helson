#include <vector>

/* Simple Pollard Rho implementation */

int gcd(int a, int b){
  int r;
  while(b != 0){
    r = a % b;
    a = b;
    b = r ;
  }
  return a;
}

int factor(int number){  
  if(number % 2 == 0) return 2;
  if(number % 3 == 0) return 3;
  if(number % 5 == 0) return 5; 
  
  int x_fixed = 2,cycle_size = 2,x = 2,factor = 1;
  
  while (factor == 1) {    
    for (int count=1;count <= cycle_size && factor <= 1;count++) {
      x = (x*x+1) % number;
      factor = gcd(x - x_fixed, number);
    }
    
    cycle_size *= 2;
    x_fixed = x;
  }
  
  return factor;   
}

int trivial_factor(int number){
  for(int i = 2; i <= number+1; i++){
    if(number % i == 0) return i; 
  }

  /* The return is only here not to trigger 
     a compiler warning */
  return 0;
  
}

void factorize(std::vector<int> &factors, int n){
  
  if(n <= 1) return;
  
  int p = factor(n);
  if(p < 0)
    p = trivial_factor(n);
  
  factors.push_back(p);
  factorize(factors, n / p);

}

