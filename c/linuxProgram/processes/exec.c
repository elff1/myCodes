#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Example of an argument list */
/* Note that we need a program name for argv[0] */
char *const ps_argv[] = {"ps", "x", 0};

/* Example environment, not terribly useful */
char *const ps_envp[] = {"PATH=/bin:/usr/bin", "TERM=console", 0};

int main(void) {
	printf("Running ps with execlp\n");
//	execlp("ps", "ps", "x", 0);
	execvp("ps", ps_argv);
	printf("Done.\n");
	exit(0);
}
