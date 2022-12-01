
#include "log.h"

std::deque<std::string> logs(MAX_LOGS);
const char* out_log = nullptr;

const char* retrieve_log(){
    out_log = std::accumulate(logs.begin(), logs.end(), std::string("")).c_str();
    return out_log;
}