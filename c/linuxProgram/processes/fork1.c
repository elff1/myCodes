#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int main(void) {
	pid_t pid;
	char *message = "hello";
	char m[10];
	int n;

	printf("fork program starting\n");
	pid = fork();
	switch(pid) {
		case -1:
			perror("fork failed");
			exit(1);
			break;
		case 0:
//			message = "child";
			strcpy(m, "child");
			n = 5;
			break;
		default:
			message = "parent";
			strcpy(m, "parent");
			n = 3;
			break;
	}

	for(; n > 0; n--) {
		puts(message);
//		puts(m);
		sleep(1);
	}
	exit(0);
}
