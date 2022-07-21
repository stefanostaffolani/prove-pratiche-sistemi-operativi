#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <unistd.h>

int buffer;
int full, empty;
ssize_t s;
uint64_t u;

void *producer(void *vargp){
	while(1){
		sleep((rand() % 5));
		int data = (rand()%10);
		s = read(empty, &u, sizeof(uint64_t));
		printf("assegno %d\n", data);
		buffer = data;
		s = write(full, &u, sizeof(uint64_t));
	}
}

void *consumer(void *vargp){
	while(1){
		sleep((rand() % 5));
		s = read(full, &u, sizeof(uint64_t));
		printf("il valore e' %d\n", buffer);
		s = write(empty, &u, sizeof(uint64_t));
	}
}

int main(int argc, char *argv[]){
	srand(time(NULL));
	full = eventfd(0,EFD_SEMAPHORE);
	empty = eventfd(1, EFD_SEMAPHORE);
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, consumer, NULL);
	pthread_create(&thread_id, NULL, producer, NULL);
	pthread_join(thread_id, NULL);
	exit(EXIT_SUCCESS);
}
