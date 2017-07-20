/* ptprodcon.c - producer consumer using semaphores */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define TRUE 1
#define FALSE 0

/* size of the buffer */
#define N 20

#define NUM_PROD 10
#define NUM_CONS 10

#define PROD 0
#define CONS 1

/* global variables shared among threads */
int buf[N];
int front = 0, rear = 0;
sem_t mutex;
sem_t full;
sem_t empty;

char *prod_str = "Producer ";
char *cons_str = "Consumer ";


int count = 0;

void print_buffer(int who, int what, int id)
{
    int i;

    char *who_str;

    who_str = (who)? cons_str : prod_str;
    
    fprintf(stderr, "%s -> %d -> %d \n", who_str, id, what);
    
    for (i=front ; i<rear ; i++)
        fprintf(stderr, " %d ", buf[i]);

    fprintf(stderr, "\n");
    return;
}


void *prod_func(void *arg)
{
    int myid = (int) arg; /* pass an int via the void * parameter */
    int iter = 0;
    
    while(iter<2) {
        /* produce an item */
        count++;

        /* wait for empty slot */
        sem_wait(&empty);

        /* Then wait for mutex access */
        sem_wait(&mutex);

        /* put item in slot */
        buf[rear] = count;
        rear = (rear+1)%N;

        /* Print the buffer */
        print_buffer(PROD, count, myid);
        
        /* leave critical section */
        sem_post(&mutex);

        /* indicate something in buffer */
        sem_post(&full);
        
        iter++;
    }
    
    pthread_exit((void *) TRUE);
}

void *cons_func(void *arg)
{
    int myid = (int) arg; /* pass an int via the void * parameter */
    int iter = 0;
    int item;
    
    while(iter<2) {
        /* wait for full slot */
        sem_wait(&full);

        /* Then wait for mutex access */
        sem_wait(&mutex);

        /* getitem from slot */
        item = buf[front];
        
        /* consume the item */
        buf[front] = 0;       
        front= (front+1)%N;

        /* Print the buffer */
        print_buffer(CONS, item, myid);
        
        /* leave critical section */
        sem_post(&mutex);

        /* indicate something in buffer */
        sem_post(&empty);
        
        iter++;
    }
    
    pthread_exit((void *) TRUE);
    
}


int main(int argc, char *argv[])
{
    pthread_t prod[NUM_PROD];
    pthread_t cons[NUM_CONS];
    int i, rv;
    
    /* initialize semaphores */
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, N);    

    /* initialize buf */
    for (i=0 ; i<N ; i++)
        buf[i] = 0;

    /* Create the producers and consumers */
/*    for (i=0 ; i<NUM_PROD ; i++)
        if (pthread_create(&prod[i], NULL, prod_func, (void *) 1) != 0) {
            printf("pthello: pthread_create error -> Producer %d\n", i);
            exit(1);
        }

    for (i=0 ; i<NUM_CONS ; i++)
        if (pthread_create(&cons[i], NULL, cons_func, (void *) 1) != 0) {
            printf("pthello: pthread_create error -> Consumer %d\n", i);
            exit(1);
            }    */

    for (i=0 ; i<NUM_PROD ; i++) {
        if (pthread_create(&cons[i], NULL, cons_func, (void *) 1) != 0) {
            printf("pthello: pthread_create error -> Consumer %d\n", i);
            exit(1);
        }        
        if (pthread_create(&prod[i], NULL, prod_func, (void *) 1) != 0) {
            printf("pthello: pthread_create error -> Producer %d\n", i);
            exit(1);
        }
    }
    

    /* Join with all the producers and consumers */
    for (i=0 ; i<NUM_PROD ; i++) {
         pthread_join(prod[i], (void **) &rv);
         printf("Main joined with Producer %d retval = %d\n", i, rv);
    }
    
    for (i=0 ; i<NUM_CONS ; i++) {
         pthread_join(cons[i], (void **) &rv);
         printf("Main joined with Consumer %d retval = %d\n", i, rv);
    }

    _exit(0);
}
