//gets Integers from stdin  and multiplies and writes them to file using pipe
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>


int main()
{
	pid_t pid;
	int fd[2], fd1[2];
	int n;
	char line[BUFSIZ];

	pipe(fd);
	pipe(fd1);
	pid = fork();

	if(pid > 0)
	{
		close(fd[0]);
		close(fd1[1]);
		printf("Input two integers ");
		while(fgets(line,BUFSIZ,stdin)!= NULL)
		{
			n = strlen(line);
			write(fd[1], line, n);
			read(fd1[0], line, BUFSIZ);
			write(1, line, strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		close(fd1[0]);
		int n1, n2, np, sum;
		char l[BUFSIZ];

		while((np = read(fd[0], l, BUFSIZ)) > 0)
		{
			if(sscanf(l, "%d %d", &n1, &n2) ==2)
			{
				sprintf(l, "%d x %d = %d\n", n1, n2, n1*n2);
				write(fd1[1], l, strlen(l));
			}
			else
			{
				sprintf(l, "Error Error Windows 95\n");
				write(fd1[1], l, strlen(l));
			}
		}
	}

	return 0;


}
