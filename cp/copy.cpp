#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char const *argv[])
{
	std::string line;
	std::ofstream out;
	std::ifstream in(argv[1]);

	out.open(argv[2]);

    while (getline(in, line))
        out << line << std::endl;
    
    in.close();

	return 0;
}