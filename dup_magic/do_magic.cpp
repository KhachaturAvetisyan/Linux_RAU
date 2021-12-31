#ifndef DO_MAGIC
#define DO_MAGIC

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void print_error(const char* error_text, const char* file)
{
    fprintf(stderr, "%s %s, (line=%i, file=%s) \n%s\n", error_text, file, __LINE__, __FILE__, strerror(errno));
    exit(EXIT_FAILURE);
}

void do_magic()
{
	const char* file = "./new_pts_0";
	int fd = open(file, O_APPEND | O_RDWR);
	if (fd < 0)
		print_error("can't open file: ", file);

	int input_file = dup2(fd, 0);
	if (input_file < 0)
		print_error("can't dup file: ", file);

	int output_file = dup2(fd, 1);
	if (output_file < 0)
		print_error("can't dup file: ", file);

	if (close(fd) < 0)
		print_error("can't close file: ", file);
}

#endif