#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include <memory>

size_t getFilesize(const char* filename) {
    struct stat st;
    if(stat(filename, &st) != 0) {
        return 0;
    }
    return st.st_size;   
}

int main(int argc, char const *argv[])
{
    size_t sof = getFilesize(argv[1]);

    int f = open(argv[1], O_WRONLY);
    if (f < 0)
    {
        fprintf(stderr, "can't open file %s, (line=%i, file=%s) \n%s\n", argv[1], __LINE__, __FILE__, strerror(errno));
	    exit(EXIT_FAILURE);
    }

    auto buf = std::unique_ptr<char[]>(new char[sof]);
    memset(buf.get(), '\0', sof);

    if (write(f, buf.get(), sof) < 0)
		{
			fprintf(stderr, "can't write in file %s, (line=%i, file=%s) \n%s\n", argv[1], __LINE__, __FILE__, strerror(errno));
	   		exit(EXIT_FAILURE);
		}

    if(close(f) < 0)
	{
	    fprintf(stderr, "can't close file %s, (line=%i, file=%s) \n%s\n", argv[1], __LINE__, __FILE__, strerror(errno));
	    exit(EXIT_FAILURE);
	}

    if(remove(argv[1]) < 0)
	{
	    fprintf(stderr, "can't remove file %s, (line=%i, file=%s) \n%s\n", argv[1], __LINE__, __FILE__, strerror(errno));
	    exit(EXIT_FAILURE);
	}
}   