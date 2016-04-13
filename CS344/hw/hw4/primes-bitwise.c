#include <math.h>
#define MAX 1000000
const int S=(int)sqrt((double)MAX);

#define rP(n) (sieve[n>>6]|=(1<<((n>>1)&31)))
#define gP(n) sieve[n>>6]&(1<<((n>>1)&31))

unsigned sieve[(MAX>>6)+1]={0};
int i, j,k,l=0 , prime[MAX];
prime[0]=2;
for(i=3;i<=S;i+=2) if(!(gP(i))) {
	k=(i<<1);
	prime[l++]=i;
	for(j=i*i;j<=MAX;j+=k) rP(j);
}

for(;i<=MAX;i++) if(!(gP(i))) prime[l++]=i;