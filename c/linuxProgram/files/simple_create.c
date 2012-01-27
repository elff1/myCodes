#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void) {
	int file;

	/** create file*/
	file = open("test", O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
	if (file < 0)
		write(2, "A create file error\n", 20);
	else {
		printf("%d\n", file);
	}

	/** close file*/
	if (close(file) < 0)
		write(2, "A close file error\n", 19);
	return(0);
}
