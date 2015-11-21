const int max_thread = 4096; 

extern unsigned long (*random_func)(unsigned long, int);
extern unsigned long (def_random)(unsigned long, int); 
extern unsigned long (srand_random)(unsigned long, int);
extern unsigned long (mersenne_random)(unsigned long, int); 
