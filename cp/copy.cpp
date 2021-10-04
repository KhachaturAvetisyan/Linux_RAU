#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char const *argv[])
{
	// std::cout << "count argc" << argc << "\n";
	// std::cout << argv[0] << "\n";
	// std::cout << argv[1] << "\n";
	// std::cout << argv[2] << "\n";

	std::string line;
	std::ofstream out;
	std::ifstream in(argv[1]);

    if (in.is_open())
    {
		out.open(argv[2]);
		if (out.is_open())
		{
	        while (getline(in, line))
	        {
	            // std::cout << line << std::endl;
        		out << line << std::endl;
	        }
    	}
    }
    in.close();

    // std::cout << line << std::endl;

	std::cout << "End of program" << std::endl;
	return 0;
}