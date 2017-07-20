/* ptsemdp.c - dining philosophers using pthreads semaphores */
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

#define N 5
sem_t forks[N];
int iters;

void *philosopher(void *arg)
{
        int id = (int) arg, i, left, right;
        struct timespec delay = {0, 0};

        if (id == 0) {
                right = id; left  = (id + 1)% N;
        } else {
                left = id; right = (id + 1)% N;
        }
        
        for (i = 0; i < iters; i++) {
                delay.tv_nsec = rand(); nanosleep(&delay, NULL);
                sem_wait(&forks[left]); sem_wait(&forks[right]);
                printf("Philosopher %d eating\n", id);
                delay.tv_nsec = rand(); nanosleep(&delay, NULL);
                sem_post(&forks[left]); sem_post(&forks[right]);
                printf("Philosopher %d thinking\n", id);
        }
}

int main(int argc, char **argv)
{
        int i;
        pthread_t t[N];

        if (argc != 2) {
                printf("usage: %s <iters>\n", argv[0]); exit(1);
        }
        iters = atoi(argv[1]);
        srand(getpid());

        for (i = 0; i < N; i++) {
                sem_init(&forks[i], 0, 1);
        }       
        for (i = 0; i < N; i++) {
                pthread_create(&t[i], NULL,  philosopher, (void *) i);
        }
        for (i = 0; i < N; i++) {
                pthread_join(t[i], NULL);
        }
}

