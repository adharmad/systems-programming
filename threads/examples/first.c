#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS		3

void * print_hello(void * threadid)
{
	int i, j, k = 0;
	printf("\nHello world from thread %d !!\n", threadid);
	for (i = 0 ; i <10000 ; i++) 
		for (j = 0 ; j <1000000 ; j++)
		k++;

	pthread_exit(NULL);
}

int main()
{
	pthread_t threads[NUM_THREADS];
	int rc, t;

	for (t=0 ; t<NUM_THREADS ; t++) {
		printf("Creating thread %d\n", t);
		rc = pthread_create(&threads[t], NULL, print_hello, (void *)t);
		if (rc) {
			printf("ERROR:return code from pthread_create() is $d\n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL); /* why this?! */
}
