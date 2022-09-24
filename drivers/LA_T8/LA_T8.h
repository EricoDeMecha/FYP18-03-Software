//
// Created by erico on 9/23/22.
//

#ifndef FYP1803_SOFTWARE_LA_T8_H
#define FYP1803_SOFTWARE_LA_T8_H

#include "mbed.h"

class LA_T8 {
public:
    LA_T8(PinName in1, PinName in2);
    bool isConnected();
    void off();
    void eject();
    void retract();
    ~LA_T8() = default;
private:
    DigitalOut _in1;
    DigitalOut _in2;
};


#endif //FYP1803_SOFTWARE_LA_T8_H
