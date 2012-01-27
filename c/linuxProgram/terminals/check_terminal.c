#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	if(!isatty(fileno(stdout))) {
		fprintf(stderr, "You are not a terminal!\n");
		exit(1);
	}
	printf("You are a terminal.\n");

	return 0;
}
