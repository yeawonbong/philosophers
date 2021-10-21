# include "philo.h"

void *thread_func(void *ptr)
{
	int count = 0;

	for(int i=0; i < 10000; i++)
		count++;
	printf("%s\n", ptr);
	return (0);
}


int main (void)
{
	char *msg1="Thread1";
	char *msg2="Thread2";

	pthread_t thread1;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	
	pthread_mutex_lock(&mutex);

	pthread_create(&thread1, NULL, thread_func, msg1);
	pthread_join(thread1, NULL);
	printf("this is main.\n");
	printf("fin_main\n");
	while(1){}
	return(0);
}