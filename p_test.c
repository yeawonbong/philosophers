# include "philo.h"

int g_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *str)
{
	pthread_mutex_lock(&mutex);
	printf("%s start\n", (char*)str);
	for(int i=0; i < 10000000; i++)
		g_count++;
	printf("%s: %d\n", (char*)str, g_count);
	pthread_mutex_unlock(&mutex);
}


int main (void)
{
	char *msg1="Thread1";
	char *msg2="Thread2";

	pthread_t thread1, thread2;
	int status;
	
	pthread_create(&thread1, NULL, thread_func, (void*)msg1);
	pthread_create(&thread2, NULL, thread_func, (void*)msg2);
	pthread_join(thread1, (void*)&status);
	pthread_join(thread2, (void*)&status);
	printf("this is main.\n");
	printf("fin_main\n");
	struct timeval starttime, endtime;
	double timegap;

	gettimeofday(&starttime, NULL);
	sleep(1);
	gettimeofday(&endtime, NULL);
	timegap = (endtime.tv_sec - starttime.tv_sec) + ((endtime.tv_usec - starttime.tv_usec) / 1000000);
	printf("time: %f\n", timegap);
	return(0);
}