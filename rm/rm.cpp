#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ftw.h>
#include <string.h>
#include <fcntl.h>

int apply_to_file(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    remove(fpath);
    return 0;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "error, please enter path files, (line=%i, file=%s) \n%s\n", __LINE__, __FILE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-r") == 0)
    {
        for (int i = 2; i < argc; ++i)
            nftw(argv[i], apply_to_file, 100, FTW_DEPTH);
    }
    else
    {
        for (int i = 1; i < argc; ++i)
        {
            int fd = open(argv[i], O_RDONLY);
            if (fd < 0)
                std::cerr << "error occured during opening the file: " << argv[i] << "\n";

            struct stat buffer;
            int status = fstat(fd, &buffer);
            if (S_ISDIR(buffer.st_mode))
                std::cerr << "error the file " << argv[i] << " is directory, please use flag -r\n";

            if (S_ISREG(buffer.st_mode))
                remove(argv[i]);
        }
    }
}