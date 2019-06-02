#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NTHREADS 4
#define N 1000
#define MEGEXTRA 100000

pthread_attr_t attr;
void *dowork(void *threadid);


int main(void)
{
	pthread_t threads[NTHREADS];
	size_t stacksize;
	int rc;
	long t;

	pthread_attr_init(&attr);
	pthread_attr_getstacksize(&attr, &stacksize);
	printf("Default stack size = %li \n", stacksize);
	stacksize = sizeof(double) * N * N + MEGEXTRA;
	printf("Amount of stack needed per tread = %li \n", stacksize);
	pthread_attr_setstacksize(&attr, stacksize);
	printf("Creating threads with stack size = %li bytes \n", stacksize);
	for ( t = 0; t < NTHREADS; ++t )
	{
		rc = pthread_create(&threads[t], &attr, dowork, &t);
		if ( rc )
		{
			printf("Error; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	printf("Created %ld threads. \n", t);
	pthread_exit(NULL);

}

void *dowork(void *threadid)
{
	double A[N][N];
	int i, j;
	long tid;
	size_t mystacksize;
	tid = *(long *)threadid;
	pthread_attr_getstacksize(&attr, &mystacksize);
	printf("Thread %ld: stack size = %li bytes \n", tid, mystacksize);
	for ( i=0; i < N; ++i )
	{
		for ( j = 0; j < N; ++j )
		{
			A[i][j] = ((i*j) / 3.452) + (N - i);
		}
		pthread_exit(NULL);
	}
	return threadid;
}
