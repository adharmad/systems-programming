/* This is my first pthread prog from the paper on pthreads given by benson */

#include <stdio.h> 
#include <pthread.h>

void print_message_function( void* ptr );

typedef struct message_tag
{
	int number;
	char* string;
}message_t;

void main()
{
	pthread_t thread1, thread2;
	message_t message1, message2;
	message1.number = 100;
	message2.number = 200;
	message1.string = "Hello!\n";
	message2.string = "World!\n";
	
	pthread_create( &thread1, NULL, 
		(void*)&print_message_function, (void*)&message1 );
	pthread_create( &thread2, NULL, 
                (void*)&print_message_function, (void*)&message2 );

	exit(0);
}

void print_message_function( void* ptr )	
{
	message_t* message;
	message = (message_t*) ptr;
	printf("%d\n", message->number);
	printf("%s", message->string);
	pthread_exit(0);
}
