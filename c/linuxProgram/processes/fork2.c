#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
	pid_t pid;
	char *message;
	char m[10];
	int n;
	int exit_code;

	printf("fork program starting\n");
	pid = fork();
	switch(pid) {
		case -1:
			perror("fork failed");
			exit(1);
			break;
		case 0:
			message = "child";
			strcpy(m, "child");
			n = 5;
			exit_code = 37;
			break;
		default:
			message = "parent";
			strcpy(m, "parent");
			n = 3;
			exit_code = 0;
			break;
	}

	for(; n > 0; n--) {
		puts(message);
//		puts(m);
		sleep(1);
	}

	if(pid != 0) {
		int stat_val;
		pid_t child_pid;
		
		child_pid = wait(&stat_val);

		printf("Child %d returns %d\n", child_pid, WEXITSTATUS(stat_val));
	}

	exit(exit_code);
}
