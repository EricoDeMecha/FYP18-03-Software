//
// Created by erico on 9/23/22.
//

#include "LA_T8.h"

LA_T8::LA_T8(PinName in1, PinName in2): _in1(in1), _in2(in2) {
    if(isConnected()){
        off();
    }
    // TODO: This is not ideal as the code will hang at this point if the relay is never connected
//    while(true){// loop until the pin is connected
//        if(isConnected()) break;
//    }
}

bool LA_T8::isConnected(){
    return _in1.is_connected() && _in2.is_connected();
}

void LA_T8::off() {
    _in1 = 1 ; _in2 = 1;
}

void LA_T8::eject() {
    _in1 = 0; _in2 = 1;
}

void LA_T8::retract() {
    _in1 =1; _in2 = 0;
}