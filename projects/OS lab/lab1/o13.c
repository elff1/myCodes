/* the third program of lab1*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/syscall.h>

/* the capacity of the buffer*/
#define BufferCapacity 5
/* the nubmer of each producer's information*/
#define InfoNum 10

void *Producer(void *arg);
void *Consumer(void *arg);

/* the information struct*/
typedef struct {
	time_t time;				// produce time
	int no;						// the cycle number
	pid_t kernelThreadID;		// kernel thread ID
	pthread_t posixThreadID;	// POSIX thread ID
} InfoStruct;

/* the full and empty semaphore*/
sem_t full, empty;
/* the mutex of shared data*/
pthread_mutex_t mutex;

/* the current size of buffer*/
int bufferSize = 0;
/* the data buffer*/
InfoStruct buffer[BufferCapacity];

int main(void) {
	pthread_t producer[2], consumer[2];
	void *proRes, *conRes;
	int res, i;

	/* initialize the semaphore and mutex*/
	res = sem_init(&full, 0, 0);
	if(res != 0) {
		perror("Semaphore full initialization");
		exit(1);
	}
	res = sem_init(&empty, 0, BufferCapacity);
	if(res != 0) {
		perror("Semaphore empty initialization");
		exit(1);
	}
	res = pthread_mutex_init(&mutex, NULL);
	if(res != 0) {
		errno = res;
		perror("Mutex initialization");
		exit(1);
	}

	/* create two consumer threads and two producer threads*/
	for(i = 0; i < 2; i++) {
		res = pthread_create(&consumer[i], NULL, Consumer, NULL);
		if(res != 0) {
			errno = res;
			perror("Thread consumer creation");
			exit(1);
		}
		res = pthread_create(&producer[i], NULL, Producer, NULL);
		if(res != 0) {
			errno = res;
			perror("Thread producer creation");
			exit(1);
		}
	}

	printf("\nWaiting for thread Consumers and Producers to finish...\n");

	/* wait for threads ending*/
	for(i = 0; i < 2; i++) {
		res = pthread_join(consumer[i], &conRes);
		if(res != 0) {
			perror("Thread consumer join");
			exit(1);
		}
		printf("Thread consumer %d joined.\n", i);
		res = pthread_join(producer[i], &proRes);
		if(res != 0) {
			perror("Thread producer join");
			exit(1);
		}
		printf("Thread producer %d joined.\n", i);
	}

	/* destroy the semaphore and mutex*/
	res = sem_destroy(&full);
	if(res != 0) {
		perror("Semaphore full destroy");
		exit(1);
	}
	res = sem_destroy(&empty);
	if(res != 0) {
		perror("Semaphore empty destroy");
		exit(1);
	}
	res = pthread_mutex_destroy(&mutex);
	if(res != 0) {
		perror("Mutex destroy");
		exit(1);
	}

	exit(0);
}

/* the producer function*/
void *Producer(void *arg) {
	int no;

	/* produce InfoNum information*/
	for(no = 1; no <= InfoNum; no++) {
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);

		/* record the information*/
		time(&buffer[bufferSize].time);
		buffer[bufferSize].no = no;
		buffer[bufferSize].kernelThreadID = syscall(SYS_gettid);
		buffer[bufferSize].posixThreadID = pthread_self();
		bufferSize++;
		sleep(1);

		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
	pthread_exit(NULL);
}

/* the consumer function*/
void *Consumer(void *arg) {
	int i;

	/* consume InfoNum information*/
	for(i = 0; i < InfoNum; i++) {
		sem_wait(&full);
		pthread_mutex_lock(&mutex);

		/* print the information*/
		bufferSize--;
		printf("kernel thread ID: %d, POSIX thread ID: 0x%x, No. %d, time: %s",
				buffer[bufferSize].kernelThreadID,
				(unsigned int)buffer[bufferSize].posixThreadID,
				buffer[bufferSize].no,
				asctime(localtime(&buffer[bufferSize].time)));
		sleep(1);
		
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
	pthread_exit(NULL);
}
