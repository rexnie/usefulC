#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

void dirwalk(char *dir, void (*f)(char *))
{
#define MAX_PATH 1024
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dirp;

	if ((dirp = opendir(dir)) == NULL) {
		perror("dirwalk: opendir error\n");
		return;
	}

	while ((dp = readdir(dirp)) != NULL) {
		if (!strcmp(dp->d_name, ".") ||
				!strcmp(dp->d_name, ".."))
			continue;
		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof (name))
			fprintf(stderr, "dirwalk name %s/%s too long\n",
					dir, dp->d_name);
		else {
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*f)(name);
		}
	}
	closedir(dirp);
}

/**
 * 打印文件name的大小
 * name 可为文件或者目录
 */
void fsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		perror("fsize: stat error %s\n");
		return;
	}

	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	else
		printf("%8ld %s\n", stbuf.st_size, name);
}

/**
 * 打印文件的大小
 */
int main(int argc, char** argv)
{
	if (argc == 1)
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	exit(0);
}
