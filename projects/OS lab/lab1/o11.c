#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define MAX_SEQUENCE 47

// the struct of the shared memory
typedef struct {
	long fib[MAX_SEQUENCE];
	int sequenceSize;
	int written;
} SharedStruct;

void Fib(int n, SharedStruct *data);

int main(int argc, char *argv[]) {
	int i;
	pid_t p1, p2;			//< the pid of two child process
	int n;						//< the input number
	char *endptr;			//< the pointer to the last char
	int shmid;				//< the shared memory identify
	void *sharedMem = (void *)0;
	SharedStruct *data;

	/* Check the parameter*/
	if(argc != 2) {
		fprintf(stderr, "Usage: %s N\n", argv[0]);
		exit(1);
	}

	errno = 0;
	n = strtol(argv[1], &endptr, 10);
	if(errno != 0) {
		perror("strtol");
		exit(1);
	}
	if(endptr == argv[1] || *endptr != '\0') {
		fprintf(stderr, "Argument type error\n");
		exit(1);
	}
	if(n > MAX_SEQUENCE) {
		fprintf(stderr, "Out of max sequence\n");
		exit(1);
	}
	else if(n < 0) {
		fprintf(stderr, "Argument shouldn't be negative\n");
		exit(1);
	}

	/* fork the first child process*/
	p1 = fork();
	if(p1 == -1) {
		perror("fork");
		exit(1);
	}
	else if(p1) {
		/* the first child process*/
		printf("Pid of 1st child process: %d\n", getpid());
		execlp("ls", "ls", "-lR", (char *)0);
		perror("execlp");
		exit(1);
	}
	wait(NULL);	//< wait for the first child process terminated

	/* Get a new shared memory identifier*/
	shmid = shmget(IPC_PRIVATE, sizeof(SharedStruct), 0666 | IPC_CREAT);
	if(shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(1);
	}

	/* Fork a second child process*/
	p2 = fork();
	switch(p2) {
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0: /* child process*/
			sharedMem = shmat(shmid, (void *)0, 0);
			if(sharedMem == (void *)-1) {
				fprintf(stderr, "shmat failed");
				exit(1);
			}

			/* get the shared memory, and write data*/
			data = (SharedStruct *)sharedMem;
			Fib(n, data);

			if(shmdt(sharedMem) == -1) {
				fprintf(stderr, "shmdt failed\n");
				exit(1);
			}
			break;
		default: /* parent process*/
			sharedMem = shmat(shmid, (void *)0, 0);
			if(sharedMem == (void *)-1) {
				fprintf(stderr, "shmat failed");
				exit(1);
			}

			data = (SharedStruct *)sharedMem;
			wait(NULL); //< wait for the second child process terminated

			/* print the data*/
			printf("The fitst %d numbers of Fibonacci sequence is:\n", n);
			for(i = 0; i < data->sequenceSize; i++) {
				printf("%ld\t", data->fib[i]);
				if(i % 8 == 7)
					putchar('\n');
			}
			if(i % 8)
				putchar('\n');

			if(shmdt(sharedMem) == -1) {
				fprintf(stderr, "shmdt failed\n");
				exit(1);
			}

			if(shmctl(shmid, IPC_RMID, 0) == -1) {
				fprintf(stderr, "shmctl(IPC_RMID) failed\n");
				exit(1);
			}
			break;
	}
	exit(0);
}

/* compute the n fibonacci numbers and write to data[]*/
void Fib(int n, SharedStruct *data) {
	int i;
	long a, b, c;

	data->sequenceSize = n;

	if(n < 1)
		return;
	data->fib[0] = 0;
	if(n < 2)
		return;
	data->fib[1] = 1;
	a = 0;
	b = 1;
	for(i = 2; i < n; i++) {
		c = a + b;
		data->fib[i] = c;
		a = b;
		b = c;
	}
}
