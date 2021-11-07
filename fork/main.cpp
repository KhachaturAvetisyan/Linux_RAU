#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define LOG_ERROR(error_text, error_file) print_error(error_text, error_file, __LINE__, __FILE__)

void print_error(const char* error_text, const char* error_file, int line, const char* file)
{
    fprintf(stderr, "%s: %s, (line=%i, file=%s) \n%s\n", error_text, error_file, line, file, strerror(errno));
    exit(EXIT_FAILURE);
}

int main()
{
	int child_process = fork();
	if (child_process < 0)
		LOG_ERROR("can't creat new process", "");
	else if(child_process == 0)
	{
		if(execlp("ls", "-a", "-l", NULL) < 0)
			LOG_ERROR("can't run file", "ls");
	}
	wait(nullptr);
}