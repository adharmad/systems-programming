/* ptmutex.c - using pthreads mutex variables for mutual exclusions */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

/* global variables shared among threads */
pthread_mutex_t gmutex;
int x = 0;

void *thread_func(void *arg)
{
        int myid = (int) arg; /* pass an int via the void * parameter */

        pthread_mutex_lock(&gmutex);
        x = x + myid;
        printf("Hello from thread %d  x = %d\n", myid, x);
        pthread_mutex_unlock(&gmutex);
        
        pthread_exit((void *) myid + 100);
}

int main(int argc, char *argv[])
{
        pthread_t t1, t2;
        int rv1, rv2;

        printf("Hello from main  x = %d\n", x);

        pthread_mutex_init(&gmutex, NULL);

        if (pthread_create(&t1, NULL, thread_func, (void *) 1) != 0) {
                printf("pthello: pthread_create error\n");
                exit(1);
        }
        if (pthread_create(&t2, NULL, thread_func, (void *) 2) != 0) {
                printf("pthello: pthread_create error\n");
                exit(1);
        }

        pthread_join(t1, (void **) &rv1);
        printf("Main joined with thread 1 retval = %d  x = %d\n", rv1, x);
        pthread_join(t2, (void **) &rv2);
        printf("Main joined with thread 2 retval = %d  x = %d\n", rv2, x);
}
/* output
$ ./ptmutex
Hello from main  x = 0
Hello from thread 1  x = 1
Hello from thread 2  x = 3
Main joined with thread 1 retval = 101  x = 3
Main joined with thread 2 retval = 102  x = 3
*/
