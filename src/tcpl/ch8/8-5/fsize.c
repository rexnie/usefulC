#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

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

char *get_rwx_str(unsigned int bits, char *rwx)
{
	rwx[3] = '\0';
	rwx[2] = bits & 01 ? 'x': '-';
	rwx[1] = bits & 02 ? 'w': '-';
	rwx[0] = bits & 04 ? 'r': '-';
	return rwx;
}

void list_stat(struct stat *st, char *name)
{
	mode_t mode;
	struct passwd *wd;
	struct group *gp;
	char fs = ' ';
	struct tm *tm, *tm_now;
	char buf[100];
	char fmt[20];
	time_t now;
	size_t i;

	mode = st->st_mode;
	if (S_ISDIR(mode))
		printf("d");
	else if (S_ISCHR(mode))
		printf("c");
	else if (S_ISBLK(mode))
		printf("b");
	else if (S_ISFIFO(mode))
		printf("f");
	else if (S_ISLNK(mode))
		printf("l");
	else if (S_ISSOCK(mode))
		printf("s");
	else if (S_ISREG(mode))
		printf("-");

	printf("%s", get_rwx_str((mode & S_IRWXU) >> 6, buf));
	printf("%s", get_rwx_str((mode & S_IRWXG) >> 3, buf));
	printf("%s", get_rwx_str((mode & S_IRWXO), buf));
	printf("%c", fs);

	printf("%ld", st->st_nlink);
	printf("%c", fs);

	if ((wd = getpwuid(st->st_uid)) != NULL) {
		printf("%-10s", wd->pw_name);
		printf("%c", fs);
	}

	if ((gp = getgrgid(st->st_gid)) != NULL) {
		printf("%-10s", gp->gr_name);
		printf("%c", fs);
	}

	printf("%8ld", st->st_size);
	printf("%c", fs);

	time(&now);
	tm_now = gmtime(&now);
	tm = gmtime(&st->st_mtime);
	strcpy(fmt, "%b %m ");
	if (tm->tm_year == tm_now->tm_year)
		strcat(fmt, "%H:%I");
	else
		strcat(fmt, "%Y");

	i = strftime(buf, sizeof(buf), fmt, tm);
	buf[i] = '\0';
	printf("%s", buf);
	printf("%c", fs);

	printf("%s\n", name);
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
		list_stat(&stbuf, name);
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
