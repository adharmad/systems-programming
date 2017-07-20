/* pthello.c - using pthreads semaphores for mutual exclusions */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

/* global variables shared among threads */
sem_t x_sem;
int x = 0;

void *thread_func(void *arg)
{
        int myid = (int) arg; /* pass an int via the void * parameter */

        sem_wait(&x_sem);
        x = x + myid;
        printf("Hello from thread %d  x = %d\n", myid, x);
        sem_post(&x_sem);
        
        pthread_exit((void *) myid + 100);
}

int main(int argc, char *argv[])
{
        pthread_t t1, t2;
        int rv1, rv2;

        printf("Hello from main  x = %d\n", x);

        sem_init(&x_sem, 0, 1);
        
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
