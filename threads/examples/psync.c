/* 
* psync.c- Pthreads synchronization *
* Programmer - GDB *
*/

#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

pthread_mutex_t lock_static = PTHREAD_MUTEX_INITIALIZER;
int shared_variable = 0;

/* define our own "create block" typ[e for starting threads */
typedef struct create_block
{
	int id;
	pthread_mutex_t* lock;
}

pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t cv_lock = PTHREAD_MUTEX_INITIALIZER;
int cv_value = 0;


