#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ftw.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
        std::cout << "error, please enter path files\n";
    

    
    // for (int i = 1; i < argc; ++i)
    // {
    //     std::cout << i << " - " << argv[i] << "\n";
    //     int f1 = unlink(argv[i]);
    //     if (f1 < 0)
    //         std::cout << "error\n";
        // int f1 = remove(argv[i]);
        // if (f1 < 0)
        //     std::cout << "error\n";
        // int dir = rmdir(argv[i]);
        // if (dir < 0)
        //     std::cout << "error\n";
    // }

    std::cout << "end\n";
}