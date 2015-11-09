# Helson's conjecture

Compiling the code requires the MPFR and GMP libraries as-well as support for threads.
The program tests Helson's conjecture by a Monte-Carlo method. To compile the code run

make 

For a static compilation run

make static

The static compilation results in slightly faster code than the non-static one.

Running

./helson N  

will estimate the first absolute moment of a random Steinhaus multiplicative functions, summed over
the first N integers. By default the number of samples is 20*N and the random variables on the unit
circle are approximated by random roots of unity of degree \sqrt{N}. In general

./helson N -i [Iter] -r [Deg] -t [Num] -m [Mom]

Will perform Iter*N iterations and approximate on roots of unity of degree Deg while using Num threads.
The recommended number for Num is the number of CPU cores available + 1. In addition the above will
compute the first Mom moments of the random variable. Two moments do not require changing the default
parameters, but computing higher moments accurately requires one to increase the number of iterations
performed. 

Finally adding the switch -R will compute the first absolute moments of a Rademacher random variable,
while adding the switch -L will dump the sampled data into the file helson.out (Warning: Possibly very
large file). 

---

The code is easily extendable if one intends to evaluate of moments of a random multiplicative function
summed over more exotic sets of integers. For example to evaluate the moments on smooth integers, all
that one needs to do is to include a function (say) bool smooth_rule(int n, int len) in rule.cc (an example
is included), include the line

extern bool smooth_rule(int, int);

in rule.h and in main.cc change the line

  rule = &default_rule;

to

  rule = &smooth_rule;

The function smooth_rule(n, len) is supposed to return true when n is smooth enough compared to len, where len
is the length of the interval [1, X] under consideration, and return false otherwise. 

Similarly the random generator is also easily extendible by editing the files random.cc, random.h and then editing
the line

  random_func = &srand_random; 

in main.cc. The current random generator is using the deafult simple linear congruential generator. While it is
weak it appears to be sufficient. Experimenting with more involved random number generators (such as the Mersenne
twister) did not yield any noticeable discrepancies in the outcomes of the simulations. 

---

