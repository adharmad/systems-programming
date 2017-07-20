/* pthello.c - a simple pthreads program */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *thread_func(void *arg)
{
        int myid = (int) arg; /* pass an int via the void * parameter */

        printf("Hello from thread %d\n", myid);

        pthread_exit((void *) myid + 100);
}

int main(int argc, char *argv[])
{
        pthread_t t1, t2;
        int rv1, rv2;

        printf("Hello from main\n");
        
        if (pthread_create(&t1, NULL, thread_func, (void *) 1) != 0) {
                printf("pthello: pthread_create error\n");
                exit(1);
        }
        if (pthread_create(&t2, NULL, thread_func, (void *) 2) != 0) {
                printf("pthello: pthread_create error\n");
                exit(1);
        }

        pthread_join(t1, (void **) &rv1);
        printf("Main joined with thread 1 retval = %d\n", rv1);
        pthread_join(t2, (void **) &rv2);
        printf("Main joined with thread 2 retval = %d\n", rv2);
}
