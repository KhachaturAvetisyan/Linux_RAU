#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <initializer_list>
#include <string>
#include <vector>
#include <iterator>

#define LR(x, y) LogRecord{x, y}

template <typename T>
struct LogRecord
{
    std::string m_key;
    T m_value;

    LogRecord(std::string key, T value)
    : m_key(std::move(key))
    , m_value(value) {}
    LogRecord() = delete;
    LogRecord(const LogRecord&) = default;
    LogRecord& operator=(const LogRecord&) = default;

    LogRecord(LogRecord&&)  noexcept = default;
    LogRecord& operator=(LogRecord&&)  noexcept = default;
    ~LogRecord() = default;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, LogRecord<T> logRec)
{
    return out << logRec.m_key << "=" << logRec.m_value << "\n";
}

namespace detail
{
    template <typename T>
    void log_fatal_helper(T&& tail)
    {
        std::cerr << tail << "\n";
        std::cerr << "closing the process: " << getpid() << "\n";
        exit(1);
    }

    template <typename T, typename ...Args>
    void log_fatal_helper(T&& head, Args&&... args)
    {
        int errno_bac = errno;
        std::cerr << head << "\n";
        log_fatal_helper(args..., strerror(errno));
    }

}

template <typename ...Args>
void log_fatal(const std::string& errorMsg, Args&&... args)
{
    std::cerr << "count of log records " << sizeof...(Args) << "\n";
    std::cerr << errorMsg << "\n";
    (std::cerr << ... << args);
}

int main()
{
	int child_process = fork();
	if (child_process < 0)
	{
        std::cerr << "can't creat new process " << "file: " << __FILE__ << "line: "
                  << __LINE__ << "desc: " <<  strerror(errno);
        exit(EXIT_FAILURE);
	}
	else if(child_process == 0)
	{
		if(execlp("ls", "-a", "-l", NULL) < 0)
		{
			std::cerr << "can't run file" << "ls" << "file: " << __FILE__ << "line: "
                  << __LINE__ << "desc: " <<  strerror(errno);
        	exit(EXIT_FAILURE);
		}
	}
	wait(nullptr);
}