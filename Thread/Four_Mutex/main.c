#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUMTHREADS 4
#define VECLEN 100000


void *dotprod(void *arg);

typedef struct
{
	double *a;
	double *b;
	double sum;
	int veclen;
} DOTDATA;

DOTDATA dotstr;
pthread_t callThd[NUMTHREADS];
pthread_mutex_t mutexsum;

int main(void)
{

	long i;
	double *a, *b;
	void *status;
	pthread_attr_t attr;

	a = (double *) malloc(NUMTHREADS * VECLEN * sizeof(double)); // define array
	b = (double *) malloc(NUMTHREADS * VECLEN * sizeof(double));


	for ( i = 0; i < VECLEN*NUMTHREADS; ++i )
	{
		a[i] = 1;
		b[i] = a[i];
	}
	dotstr.veclen = VECLEN;
	dotstr.a = a;
	dotstr.b = b;
	dotstr.sum = 0;
	pthread_mutex_init(&mutexsum, NULL);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for ( i = 0; i < NUMTHREADS; ++i )
	{
		pthread_create(&callThd[i], &attr, dotprod, (void *)i);
	}
	pthread_attr_destroy(&attr); // destroy attr

	for ( i = 0; i < NUMTHREADS; ++i )
	{
		pthread_join(callThd[i], &status); // join this thread
	}

	printf("Sum = %f \n", dotstr.sum);
	free(a); // release of the memory
	free(b);
	pthread_mutex_destroy(&mutexsum); // destroy the mutex lock
	pthread_exit(NULL); // exit pthread

	return 0;

}

// 进行运算
void *dotprod(void *arg)
{
	int i, start, end, len;
	long offset;
	double mysum, *x, *y;
	offset = (long)arg;

	len = dotstr.veclen;
	start = offset *len;
	end = start + len;
	/* printf("len=%d, start=%d, end=%d\n", len, start, end); */
	x = dotstr.a;
	y = dotstr.b;

	mysum = 0;
	for ( i = start; i < end; ++i )
	{
		mysum += (x[i] * y[i]);
	}
	pthread_mutex_lock (&mutexsum); // lock the thread when per loop
	dotstr.sum += mysum;
	printf("Thread %ld did %d to %d: mysum=%f global sum=%f\n", offset, start, end, mysum, dotstr.sum);
	pthread_mutex_unlock (&mutexsum); // unlock when thread completed
	pthread_exit(NULL);

}
