#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 5

void *PrintHello(void *threadid);

int main(int argc, char * argv[])
{

	pthread_t threads[NUM_THREADS];
	int rc;
	int t;
	for ( t = 0; t < NUM_THREADS; ++t )
	{
		printf("In main: creating thread %d\n", t); // 主线程
		rc = pthread_create(&threads[t], NULL, PrintHello, &t); // 子线程执行的函数, 接受t为PrintHello的参数
		/* sleep(1); */
		if (rc)
		{
			printf("ERROR: return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);

	return 0;
}


void *PrintHello(void *threadid)
{
	printf("Hello, World! It's me, thread #%d\n", *(int *)threadid);
	pthread_exit(NULL);
}
