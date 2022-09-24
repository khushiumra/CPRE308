/* Author: Khushveen Kaur Umra, kumra@iastate.edu */

#include <pthread.h>
#include <stdio.h>

/* To create two thread functions */

void* thread1();
void* thread2();


int main() {

	pthread_t i1, i2; /* variables of datatype pthread_t */

	/* Functions to create both threads i1 & i2 */

	pthread_create(&i1, NULL, (void*)&thread1, NULL);
	pthread_create(&i2, NULL, (void*)&thread2, NULL);

	/* Wait for the threads to finish before printing the message */

	pthread_join(i1, NULL);
	pthread_join(i2, NULL);

	printf("Hello from main\n");

	return 0;
}

void* thread1() {
	sleep(5); /* Prints after 5 seconds */ 
	printf("Hello from thread1\n");
}

void* thread2() {
	sleep(5); /* Prints after 5 seconds */
	printf("Hello from thread2\n");
}


