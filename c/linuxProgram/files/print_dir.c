#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *dir, int depth) {
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	if ((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "cannot open directory: %s\n", dir);
		return;
	}
	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode)) {
			/* Found a directory, but igonre . and .. */
			if(strcmp(".", entry->d_name) == 0 ||
					strcmp("..", entry->d_name) == 0)
				continue;
			printf("%*s%s/\n", depth, "", entry->d_name);
			/* Recurse at a new indent level */
			printdir(entry->d_name, depth + 4);
		}
		else
			printf("%*s%s\n", depth, "", entry->d_name);
	}
	chdir("..");
	closedir(dp);
}

int main(void) {
	char path[128];
	int nread;

	nread = read(0, path, 128);
	if (nread == -1)
		write(2, "A read error has occured\n", 26);
	*strchr(path, '\n') = 0;

	printf("Directory scan of %s:\n", path);
	printdir(path, 0);
	printf("done.\n");

	return 0;
}
