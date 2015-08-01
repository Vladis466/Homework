


#ifndef PRIMES_H
#define PRIMES_H
struct primeArr
	{
		long *num;				
		int num_of_primes;			
		long capacity;
		long *list;
	};

void p_primeArr(struct primeArr *Arr);
void IgnorePts(struct primeArr *Arr);
struct primeArr *crinit_primeArr(long t);


#endif /* PRIMES_H  */