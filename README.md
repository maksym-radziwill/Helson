# Helson

Running the code requires having the MPFR and GMP libraries install as-well as support for threads.
The program tests helson's conjecture by a Monte-Carlo method.

./helson N

Will estimate the first absolute moment of a random Steinhaus multiplicative functions, summed over
the first N integers. By default the number of sample is 20*N and the random variables on the unit
circle are approximated by roots of unity of degree \sqrt{N}. In general

./helson N -i [Iter] -r [Deg] -t [Num] -m [Mom]

Will perform Iter*N iterations and approximate on roots of unity of degree Deg while using Num threads.
The recommended number for Num is the number of CPU cores available + 1. In addition the above will
compute the first Mom moments of the random variable. Two moments do not require changing the default
parameters, but going into higher moments requires one to increase the number of Iterations performed. 

Finally adding the switch -R will compute the first absolute moments of a Rademacher random variable,
while adding the switch -L will log the sampled data into the file helson.out (Warning: Possibly very
large file). 

---

The code is easily extendable to evaluate moments of a random multiplicative function supported on
more exotic sets of integers. For example to evaluate the moments on smooth integers, all that one
needs to do is to include a function smooth_rule in rule.cc (an example is included) and in main.cc
change the line

  rule = &default_rule;

to

  rule = &smooth_rule;

Similarly the function generating randomness is also easily extendible by editing the file random.cc
and then editing the line

  random_func = &srand_random; 

in main.cc.
