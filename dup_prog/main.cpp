#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void print_error(const char* error_text, const char* file)
{
    fprintf(stderr, "%s %s, (line=%i, file=%s) \n%s\n", error_text, file, __LINE__, __FILE__, strerror(errno));
    exit(EXIT_FAILURE);
}

int main()
{
    const char* const file = "exclusive_file.log";
    int fd = open(file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd < 0)
	    print_error("can't open file", file);

    int copy_fd = dup(fd);

    char* input_text = "First line\n";

    if (write(copy_fd, input_text, strlen(input_text)) < 0)
        print_error("can't write file", file);

    input_text = "Second line\n";

    if (write(fd, input_text, strlen(input_text)) < 0)
        print_error("can't write file", file);

    if (close(fd) < 0)
        print_error("can't close file", file);
}