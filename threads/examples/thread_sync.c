/* In this program 2 threads communicate using a shared buffer which they
lock using mutexes and condition variables 
From benson's paper */

#include <stdio.h>
#include <pthread.h>

void reader_function(void);
void writer_function(void);

char buffer;
int buffer_has_item = 0;
pthread_mutex_t mutex;
struct timespec delay;

char make_new_item()
{
	char c = 'M';
	return c;
}

char consume_buffer( char buf )
{
	return buf;
}

void main()
{
	pthread_t reader;

	delay.tv_sec = 2;
	delay.tv_nsec = 0;

	pthread_mutex_init( &mutex, NULL );
	pthread_create( &reader, NULL, (void*)&reader_function, 
		NULL );
	writer_function();
} 

void writer_function( void )
{
	char c;
	scanf("%c\n", &c);

	while(1)
	{
		pthread_mutex_lock( &mutex );
		if ( buffer_has_item == 0 )
		{
			buffer = make_new_item(c);
			buffer_has_item = 1;
		}
		pthread_mutex_unlock( &mutex );
//		pthread_delay_np( &delay );
	}
}

void reader_function( void )
{
	char c;
 
	while(1)
	{
		pthread_mutex_lock( &mutex );
		if ( buffer_has_item == 1 )
		{
			c = consume_buffer( buffer );
			printf("message is %c\n", c);
			buffer_has_item = 0;
			pthread_exit(0);
		}
		pthread_mutex_unlock( &mutex );
//		pthread_delay_np( &delay );
	}
}

