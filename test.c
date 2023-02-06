#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

//void	check_leak(void)
//{
//	system("leaks --list -- a.out");
//}


int main()
{
	int fd1 = open("test.txt", O_RDONLY);
	char *buf;
	int i = 0;

	while (i < 6)
	{
		buf = get_next_line(fd1);
		printf("%s",buf);
		free(buf);
		buf = NULL;
		i++;
	}
	close(fd1);
//	atexit(check_leak);
}
