#include <iostream>
#include <string>
#include <pthread.h>


#define LOG_TRACE(...) Logger::Trace(__LINE__, __FILE__,  __VA_ARGS__)
#define LOG_WARNING(...) Logger::Warning(__LINE__, __FILE__, __VA_ARGS__)
#define LOG_ERROR(...) Logger::Error(__LINE__, __FILE__, __VA_ARGS__)


enum LogState
{
	trace, warning, error
};

class Logger
{
private:
	static LogState state;
	pthread_mutex_t lock;

public:
	static void set_state(LogState new_state)
	{
		state = new_state;
	}

	template <typename... Args>
	static void Trace(int line, const char* file, Args... args)
	{
		if (state <= trace)
		{

			std::cout << "[Trace]\t";
		 	((std::cout << args << " "), ...);
		 	std::cout << "\nl:" <<  line << " f:" << file << ".\n";

		}
	}

	template<typename... Args>
	static void Warning(int line, const char* file, Args... args)
	{
		if (state <= warning)
		{

			std::cout << "[Warning]\t";
		 	((std::cout << args << " "), ...);
		 	std::cout << "\nl:" <<  line << " f:" << file << ".\n";

		}
	}

	template<typename... Args>
	static void Error(int line, const char* file, Args... args)
	{
		if (state <= error)
		{

			std::cerr << "[Error]\t";
		 	((std::cerr << args << " "), ...);
		 	std::cerr << "\nl:" <<  line << " f:" << file << ".\n";
		    exit(EXIT_FAILURE);

		}
	}

};

LogState Logger::state = trace;