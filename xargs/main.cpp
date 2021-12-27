#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		std::cerr << "please enter the command in the arguments\n" << "file: " << __FILE__ << " line: "
                  << __LINE__ << " desc: " <<  strerror(errno) << "\n";
        exit(EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		std::cerr << "you entered too many commands in the arguments\n" << "file: " << __FILE__ << " line: "
                  << __LINE__ << " desc: " <<  strerror(errno) << "\n";
          exit(EXIT_FAILURE);
	}
	else
	{
		std::string input;

		while (std::cin >> input)
		{
			int process_id = fork();
			if (process_id < 0)
			{
		        std::cerr << "can't creat new process " << "file: " << __FILE__ << " line: "
		                  << __LINE__ << " desc: " <<  strerror(errno) << "\n";
		        exit(EXIT_FAILURE);
			}
			else if(process_id == 0)
			{
				if(execlp(argv[1], argv[1], input.c_str(), NULL) < 0)
				{
					std::cerr << "can't run file " << argv[1] << "file: " << __FILE__ << " line: "
		                  << __LINE__ << " desc: " <<  strerror(errno) << "\n";
		        	exit(EXIT_FAILURE);
				}
			}
			wait(nullptr);
		}

	}

	return 0;
}