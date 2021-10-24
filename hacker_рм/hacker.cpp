#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>

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
        std::cout << "error\n";

    char *buf= new char[sof];
    memset(buf, '\0', sof);

    write(f, buf, sof);

    close(f);

    delete[] buf; 

    remove(argv[1]);
}   