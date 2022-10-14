#include "globals.h"


Servo servo(PC_8);//calibration for an MG996R Servo motor
LA_T8 laT8(PE_6, PC_13);
DS1820 ds18b20(PE_2);
HX711 hx711(3.2f, PB_10, PE_15, 32);    // avdd in Volts, sck pin, dout pin, gain
AppController appController;

std::deque<const char*> logs(MAX_LOGS);
template<typename ... Args>
void log( const std::string& format, Args ... args ){
    int size_s = std::snprintf( nullptr, 0, "%s", format.c_str(), args ... ) + 1; // Extra space for '\0'
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, "%s", format.c_str(), args ... );
    // store
    if(logs.size() == MAX_LOGS){
        logs.pop_front();
    }
    logs.emplace_back(buf.get());
}