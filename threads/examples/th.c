#include <stdio.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mut;

void printError(int x){
    switch(x){
        case EBUSY:
            printf("Mutex is busy\n");
            break;

        case EINVAL:
            printf("Not a valid mutex\n");
            break;

        case EDEADLK:
            printf("Deadlock condition\n");
            break;
    }
    return;
}


void* threadProc(void* foo){

    int x;
    
	if ( (x=pthread_mutex_trylock(&mut)) == -1 )
        printError(x);

    printf("after trylock\n");

	if ( (x=pthread_mutex_unlock(&mut)) == -1 )
        printError(x);

    printf("after trylock unlock\n");
    
	if ( (x=pthread_mutex_lock(&mut)) == -1 )
        printError(x);

    printf("after lock\n");
    
	if ( (x=pthread_mutex_unlock(&mut)) == -1 )
        printError(x);

    printf("after lock unlock\n");
    
	return NULL;
}

int
main(int argc, char** argv) {
	pthread_t thread;
    pthread_attr_t attr;
    int x;
    void* foo = NULL;
    pthread_mutexattr_t mta;

    if ( (x=pthread_mutexattr_init(&mta)) != 0 ) {
        printf("Error initializing mutex attr\n");
        printError(x);
    }
    
    if ( (x=pthread_mutex_init(&mut, &mta)) == -1 ) {
        printf("Error initializing mutex\n");
        printError(x);
    }

	if ( (x=pthread_mutex_lock(&mut)) != 0 )
        printError(x);

	if ( pthread_create(&thread, NULL, threadProc, foo)  == -1 )
        printf("Pthread create error\n");
    

    printf("before main unlock\n");
    
    if ( (x=pthread_mutex_unlock(&mut)) != 0) {
        printf("Mutex unlock error\n");
        printError(x);
    }
    
    printf("after main unlock\n");

	pthread_mutex_destroy(&mut);

    pthread_join(thread, NULL);

	return 0;
}


