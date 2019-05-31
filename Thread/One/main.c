#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 7

void *PrintHello(void *threadArg);
char *messages[NUM_THREADS];

struct thread_data
{
	int thread_id;
	int sum;
	char *messages;
};

struct thread_data thread_data_array[NUM_THREADS];

int main(int argc, char * argv[])
{

	pthread_t threads[NUM_THREADS];
	/* int *taskids[NUM_THREADS]; */
	int rc, t, sum;
	sum = 0;
	messages[0] = "English: Hello, world!";
	messages[1] = "French: Bonjour, le monde!";
	messages[2] = "Spanish: hola al mundo";
	messages[3] = "Klingon: Nuq neH";
	messages[4] = "Japan: Sekai e konnichiwa!";
	messages[5] = "Latin: Orbis, te saluto!";
	messages[6] = "Chinese: 你好, 世界!";
	
	for ( t = 0; t < NUM_THREADS; ++t )
	{
		sum = sum + t;
		thread_data_array[t].thread_id = t;
		thread_data_array[t].sum = sum;
		thread_data_array[t].messages = messages[t];
		
		printf("In main: creating thread %d\n", t); // 主线程
		rc = pthread_create(&threads[t], NULL, PrintHello, &thread_data_array[t]); // 子线程执行的函数, 接受t为PrintHello的参数
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


void *PrintHello(void *threadArg)
{
	int taskid, sum;
	char *hello_msg;
	struct thread_data *my_data;
	sleep(3);
	my_data = (struct thread_data *) threadArg;
	taskid = my_data->thread_id;
	sum = my_data->sum;
	hello_msg = my_data->messages;
	printf("Thread %d: %s   Sum=%d\n", taskid, hello_msg, sum);
	pthread_exit(NULL);
}
