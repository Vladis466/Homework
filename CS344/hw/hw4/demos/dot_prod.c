#define _POSIX_C_SOURCE 200908L

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 8
#define VEC_LEN 1000000




struct data
{
	double *a;
	double *b;
	int len;
	int offset;
};

pthread_t threads[NUM_THREADS];

pthread_mutex_t mutex_sum;
double sum;

void *dot(void *arg)
{
	int start;
	int end;
	int length;
	double *x;
	double *y;
	double sub_sum;

	struct data *d = (struct data*) arg;

	length = d->len;
	start = d->offset * length;
	end = start + length;
	x = d->a;
	y = d->b;
	
	sub_sum = 0.0;

	for(int i=start; i<end; ++i)
	{
		
		sub_sum += x[i] * y[i];
		
	}
	pthread_mutex_lock(&mutex_sum);
	sum += sub_sum;
	pthread_mutex_unlock(&mutex_sum);

	pthread_exit((void*) 0);
}

int main(int argc, char **argv)
{
	double *a = (double*)malloc(NUM_THREADS * VEC_LEN * sizeof(double));
	double *b = (double*)malloc(NUM_THREADS * VEC_LEN * sizeof(double));

	struct data d[NUM_THREADS];

	pthread_attr_t attr;

	for(int i=0; i<VEC_LEN * NUM_THREADS; ++i)
	{
		a[i] = 1.0;
		b[i] = 1.0;
	}

	sum = 0.0;

	pthread_mutex_init(&mutex_sum, NULL);

	pthread_attr_init(&attr);

	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(int i=0; i<NUM_THREADS; ++i)
	{
		d[i].a = a;
		d[i].b = b;
		d[i].offset = i;
		d[i].len = VEC_LEN;
		pthread_create(&threads[i], &attr, dot, (void*)&d[i]);
	}

	pthread_attr_destroy(&attr);

	for(int i=0; i<NUM_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	printf("Sum is %f\n", sum);

	free(a);
	free(b);

	pthread_mutex_destroy(&mutex_sum);
	
	return EXIT_SUCCESS;
}
