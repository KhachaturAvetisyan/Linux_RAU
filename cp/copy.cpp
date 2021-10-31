#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int read_fd = open(argv[1], O_RDONLY);
	if(read_fd < 0)
	{
	    fprintf(stderr, "can't open file %s, (line=%i, file=%s) \n%s", argv[1], __LINE__, __FILE__, strerror(errno));
	    exit(EXIT_FAILURE);
	}

	int write_fd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(write_fd < 0)
	{
	    fprintf(stderr, "can't open file %s, (line=%i, file=%s) \n%s", argv[2], __LINE__, __FILE__, strerror(errno));
	    exit(EXIT_FAILURE);
	}
	
	char buf;

	while(read(read_fd, &buf, 1) > 0)
	{
		if (write(write_fd, &buf, 1) < 0)
		{
			fprintf(stderr, "can't write in file %s, (line=%i, file=%s) \n%s", argv[2], __LINE__, __FILE__, strerror(errno));
	   		exit(EXIT_FAILURE);
		}
	}

	if(close(read_fd) < 0)
	{
	    fprintf(stderr, "can't close file %s, (line=%i, file=%s) \n%s", argv[1], __LINE__, __FILE__, strerror(errno));
	    exit(EXIT_FAILURE);
	}
	if(close(write_fd) < 0)
	{
	    fprintf(stderr, "can't close file %s, (line=%i, file=%s) \n%s", argv[2], __LINE__, __FILE__, strerror(errno));
	    exit(EXIT_FAILURE);
	}

	return 0;
}