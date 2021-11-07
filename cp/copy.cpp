#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define LOG_ERROR(error_text, error_file) print_error(error_text, error_file, __LINE__, __FILE__)

void print_error(const char* error_text, const char* error_file, int line, const char* file)
{
    fprintf(stderr, "%s %s, (line=%i, file=%s) \n%s\n", error_text, error_file, line, file, strerror(errno));
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
	int read_fd = open(argv[1], O_RDONLY);
	if(read_fd < 0)
		LOG_ERROR("can't open file,", argv[1]);

	int write_fd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(write_fd < 0)
		LOG_ERROR("can't open file,", argv[2]);
	
	const size_t size_buf = 4096;
	char* buf[size_buf];
	int read_text = -1;

	while(true)
	{
		if ((read_text = read(read_fd, &buf, size_buf)) <= 0)
			break;

		if (write(write_fd, &buf, read_text) < 0)
			LOG_ERROR("can't write file,", argv[2]);
	}

	if(close(read_fd) < 0)
		LOG_ERROR("can't, close file,", argv[1]);
	if(close(write_fd) < 0)
		LOG_ERROR("can't, close file,", argv[2]);
}