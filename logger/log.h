#include "mbed.h"
#include <deque>
#include <numeric>
#include <string>

#define MAX_LOGS 13

// logging container
extern  std::deque<std::string> logs;
extern  const char* out_log;

template<typename ... Args>
extern void log( const std::string& format, Args ... args );

extern const char* retrieve_log();