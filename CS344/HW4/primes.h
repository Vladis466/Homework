


#ifndef PRIMES_H
#define PRIMES_H
struct primeArr
	{
		char *num;
		char *mask;
		int num_of_primes;			
		long capacity;
	};

void p_primeArr(struct primeArr *Arr);
void IgnorePts(struct primeArr *Arr);
struct primeArr *crinit_primeArr(long t);
int bmask(long index, char *bitMask);
void mapPrimes(char *bitArr, long Count);

#endif /* PRIMES_H  */