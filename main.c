#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"



int	main(void)
{
	int	fd;
	int	reading;
	char	*buffer;

	buffer = (char*)malloc(BUFFER_SIZE + 1);
	fd = open("test.txt", O_RDONLY);
	reading = read(fd, buffer, BUFFER_SIZE);
	printf("buffer = %s", buffer);
}

/*
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
	}
	return (0);*/