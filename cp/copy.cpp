#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int f1 = open(argv[1], O_RDONLY);
	int f2 = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	char buf;

	while(read(f1, &buf, 1))
		write(f2, &buf, 1);

	close(f1);
	close(f2);

	return 0;
}