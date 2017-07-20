/* ptcvdp.c - dining philosophers using pthreads condition variables */
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

#define N 5
int forks[] = {2, 2, 2, 2, 2};
pthread_mutex_t dp_mutex;
pthread_cond_t both_free[N];
int right[] = {1, 2, 3, 4, 0};
int left[]  = {4, 0, 1, 2, 3};
int iters;

void getforks(int i)
{
        pthread_mutex_lock(&dp_mutex);
        if (forks[i] < 2) pthread_cond_wait(&both_free[i], &dp_mutex);
        forks[right[i]]--;
        forks[left[i]]--;
        pthread_mutex_unlock(&dp_mutex);
}

void relforks(int i)
{
        pthread_mutex_lock(&dp_mutex);
        forks[right[i]]++;
        forks[left[i]]++;
        if (forks[right[i]] == 2) pthread_cond_signal(&both_free[right[i]]);
        if (forks[left[i]] == 2) pthread_cond_signal(&both_free[left[i]]);
        pthread_mutex_unlock(&dp_mutex);
}

void *philosopher(void *arg)
{
        int id = (int) arg, i;
        struct timespec delay = {0, 0};

        for (i = 0; i < iters; i++) {
                delay.tv_nsec = rand(); nanosleep(&delay, NULL);
                getforks(id);
                printf("Philosopher %d eating\n", id);
                delay.tv_nsec = rand(); nanosleep(&delay, NULL);
                relforks(id);
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

        pthread_mutex_init(&dp_mutex, NULL);

        for (i = 0; i < N; i++) {
                pthread_cond_init(&both_free[i], NULL);
        }       
        for (i = 0; i < N; i++) {
                pthread_create(&t[i], NULL,  philosopher, (void *) i);
        }
        for (i = 0; i < N; i++) {
                pthread_join(t[i], NULL);
        }
}

