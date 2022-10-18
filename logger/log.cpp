#include "log.h"


std::deque<std::string> logs(MAX_LOGS);
const char* out_log = nullptr;

template<typename ... Args>
void log( const std::string& format, Args ... args ){
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    // store
    if(logs.size() == MAX_LOGS){
        logs.pop_front();
    }
    logs.emplace_back(std::string( buf.get(), buf.get() + size - 1 ));
}

const char* retrieve_log(){
    out_log = std::accumulate(logs.begin(), logs.end(), std::string("")).c_str();
    return out_log;
}