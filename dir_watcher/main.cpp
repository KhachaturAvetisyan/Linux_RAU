#include <iostream>
#include <sys/inotify.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include "logger.h"


constexpr int event_size = sizeof(struct inotify_event);
constexpr int event_buf_len = 1024 * ( event_size);


const std::string currentDateTime() 
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "\n%Y-%m-%d %X\n\n", &tstruct);

    return buf;
}


void write_to_file(int fd, std::string massage)
{
  const void* m = massage.c_str();

  if (write(fd, m, massage.size()) < 0)
  {
    LOG_ERROR("can't write in file:", "./log");
  }
}


int main(int argc, char const *argv[])
{
  Logger::set_state(warning);

  // check argumnet main
  if (argc < 2)
  {
    LOG_ERROR("Please enter the directory in the arguments.");
  }

  // create log file descriptor
  int log_fd = open("./log", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (log_fd < 0)
  {
    LOG_ERROR("can't open file:", "./log");
  }

  // write to log_file time
  std::string time = currentDateTime();
  LOG_TRACE(time);
  write_to_file(log_fd, time);

  // create event struct and variables
  const struct inotify_event *event;
  size_t len;
  char buffer[event_buf_len];

  // create file descriptor associated with a new inotify event queue
  int fd = inotify_init();
  if ( fd < 0 )
  {
    LOG_ERROR("can't inotify init");
  }

  // add a watch to an initialized inotify instance
  int wd = inotify_add_watch( fd, argv[1], IN_CREATE | IN_DELETE );
  if ( wd < 0 )
  {
    LOG_ERROR("can't inotify add watch");
  }

  for (;;)
  {
    int length = read( fd, buffer, event_buf_len);

    int i = 0;

    while ( i < length ) 
    { 
      struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];     
      if ( event->len ) 
      {
        if ( event->mask & IN_CREATE ) 
        {
          if ( event->mask & IN_ISDIR ) 
          {
            std::string massage = "Created new directory: ";
            massage += event->name;
            massage += ".\n";

            LOG_TRACE(massage);

            write_to_file(log_fd, massage);            
          }
          else 
          {
            std::string massage = "New file ";
            massage += event->name;
            massage += " created.\n";

            LOG_TRACE(massage);

            write_to_file(log_fd, massage);   
          }
        }
        else if ( event->mask & IN_DELETE ) 
        {
          if ( event->mask & IN_ISDIR ) 
          {
            std::string massage = "Directory ";
            massage += event->name;
            massage += " deleted.\n";

            LOG_TRACE(massage);

            write_to_file(log_fd, massage);
          }
          else 
          {
            std::string massage = "File ";
            massage += event->name;
            massage += " deleted.\n";

            LOG_TRACE(massage);

            write_to_file(log_fd, massage);
          }
        }
      }
      i += event_size + event->len;
    }
  }

  // delete watch
  if (inotify_rm_watch( fd, wd ) < 0)
  {
    LOG_WARNING("can't inotify rm watch");
  }

  if (close( log_fd ) < 0)
  {
    LOG_WARNING("can't close log_fd");
  }

  // close file descriptor
  if (close( fd ) < 0)
  {
    LOG_WARNING("can't close file: ", "./log");
  }

  return 0;
}